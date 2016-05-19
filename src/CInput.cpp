#include "record_final.h"
#include <typeinfo>

CInput::CInput()
{
	
}

CInput::~CInput()
{
	
}

struct CInput::InputData {
	MY_TYPE* buffer;
	unsigned long bufferBytes;
	unsigned long totalFrames;
	unsigned long frameCounter;
	unsigned int channels;
	unsigned int sampleRate;
};	


bool CInput::WithCorrectSampleRate()
{
	return inputSampleRate == DEFAULT_SAMPLE_RATE;
}

	


MY_TYPE* CInput::Rediscretization(MY_TYPE* recording, double time, int sampleRateOfRecord)
{
	if(sampleRateOfRecord != DEFAULT_SAMPLE_RATE)
	{
		return Decimation(recording, time, sampleRateOfRecord, DEFAULT_SAMPLE_RATE);
	}
	return recording;
}

MY_TYPE* CInput::Decimation(MY_TYPE* recording, double time, int sampleRateOfRecord, int sampleRateNeeded)
{
	size_t sampleRateRatio = sampleRateOfRecord / sampleRateNeeded;
	
	if (sampleRateRatio == 1) 
		return recording;
	
	MY_TYPE* tmpBuffer;
	tmpBuffer = new MY_TYPE [ (unsigned int)(sampleRateOfRecord * time / sampleRateRatio) * sizeof(MY_TYPE)];
	
	
	size_t counter = 0;  
	size_t jiter = 0;
	for (size_t iter = 0; iter < sampleRateOfRecord * time; iter+=sampleRateRatio)
	{
		counter = 0;
		tmpBuffer[jiter] = 0;
		while(counter < sampleRateRatio)
		{
			tmpBuffer[jiter] += (double) (recording[iter + counter] / sampleRateRatio);
			counter++;
		}
		jiter++;
		
	}

	return tmpBuffer;
}

std::vector<MY_TYPE> CInput::RecordMelody()
{
	unsigned int sampleRate, bufferFrames, /*device = 0,*/ offset = 0; 
	unsigned int channels = 1; // Mono audio
	double time = 10.0;
	FILE *rawFile;

	RtAudio adc;
	RtAudio::DeviceInfo info;
	
	if ( adc.getDeviceCount() < 1 ) {
	std::cout << "\nNo audio devices found!\n";
		return std::vector<double>();
	}
	
  
	// Search for default input device  
	for (unsigned int i=0; i < adc.getDeviceCount(); i++) {
		info = adc.getDeviceInfo(i);
		if(info.isDefaultInput)
			break;
	}
  
	// Choosing sample rate closest to the default samle rate  
	if ( info.sampleRates.size() < 1 )
		std::cout << "No supported sample rates found!";
	else {
		std::cout << "Supported sample rate (closest to " << DEFAULT_SAMPLE_RATE << ") = ";
		for(size_t i = 0; i < info.sampleRates.size(); i++)
		{
			sampleRate = info.sampleRates[i];   
			if ((info.sampleRates[i] >= DEFAULT_SAMPLE_RATE) && 
				(info.sampleRates[i] % DEFAULT_SAMPLE_RATE == 0)) 
				break;
		}	     
		std::cout << sampleRate << std::endl;
	}
	
	if (sampleRate % DEFAULT_SAMPLE_RATE != 0)
	{
		std::cout << "\nNo supported sample rate!\n";
		return std::vector<double>();
	}
	
	// Let RtAudio print messages to stderr.
	adc.showWarnings( true );

	// Set our stream parameters for Input only.
	bufferFrames = 512;
	RtAudio::StreamParameters iParams;
	
	iParams.nChannels = channels;
	iParams.firstChannel = offset;
	iParams.deviceId = adc.getDefaultInputDevice();
	InputData data;
	data.buffer = 0;
      
	try {
		adc.openStream( NULL, &iParams, FORMAT, sampleRate, &bufferFrames, &Input, (void *)&data );
	}
	catch ( RtAudioError& e ) {
		std::cout << '\n' << e.getMessage() << '\n' << std::endl;
		if ( adc.isStreamOpen() ) adc.closeStream();
		if ( data.buffer ) delete [] data.buffer;
		
		std::cout << "\n!\n";
		
		return std::vector<double>();
	}

	// Initialization data buffer
	data.bufferBytes = bufferFrames * channels * sizeof( MY_TYPE );
	data.totalFrames = (unsigned long) (sampleRate * time);
	data.frameCounter = 0;
	data.channels = channels;
	data.sampleRate = sampleRate;
	unsigned long totalBytes;
	totalBytes = data.totalFrames * channels * sizeof( MY_TYPE );

	// Allocate the entire data buffer before starting stream.
	
	data.buffer = new MY_TYPE [totalBytes];
	
	if ( data.buffer == 0 ) {
		std::cout << "Memory allocation error ... quitting!\n";
		return std::vector<double>();
	}

	// Stream start.
	try {
		adc.startStream();
	}
	catch ( RtAudioError& e ) {
		std::cout << '\n' << e.getMessage() << '\n' << std::endl;
		if ( adc.isStreamOpen() ) adc.closeStream();
			delete [] data.buffer;
		return std::vector<double>();
	}

	std::cout << "\nRecording for " << time << " seconds ... " << std::endl;
	
	while ( adc.isStreamRunning() ) {
		SLEEP( 100 ); // wake every 100 ms to check if we're done
	}

	// Rediscretisation:
	std::vector<MY_TYPE> rediscretizatedRecord;
	MY_TYPE* newBufferForRediscret;
	//
	if ( sampleRate != DEFAULT_SAMPLE_RATE)
		newBufferForRediscret = Rediscretization(data.buffer, time, sampleRate);
	delete [] data.buffer;
	data.buffer = newBufferForRediscret;

	std::vector<MY_TYPE> interpolatedRecord(data.buffer, data.buffer + sizeof data.buffer / sizeof data.buffer[0]);
	rawFile = fopen( "record.raw", "wb" );
	fwrite( &data.buffer[0], sizeof( MY_TYPE ),  (unsigned long) (DEFAULT_SAMPLE_RATE * time) * channels, rawFile );  
	fclose( rawFile );
    
	if ( adc.isStreamOpen() ) adc.closeStream();
	if (data.buffer)	delete [] data.buffer;
	std::cout << "Recording Successful. Proceeding...\n" << std::endl;
	return interpolatedRecord;
}

// Interleaved buffers
int Input( void * /*outputBuffer*/, void *inputBuffer, unsigned int nBufferFrames,
           double /*streamTime*/, RtAudioStreamStatus /*status*/, void *data )
{
	CInput::InputData *iData = (CInput::InputData *) data;

	// Simply copy the data to our allocated buffer.
	unsigned int frames = nBufferFrames;
	if ( iData->frameCounter + nBufferFrames > iData->totalFrames ) {
		frames = iData->totalFrames - iData->frameCounter;
		iData->bufferBytes = frames * iData->channels * sizeof( MY_TYPE );
	}

	unsigned long offset = iData->frameCounter * iData->channels;
	memcpy( iData->buffer+offset, inputBuffer, iData->bufferBytes );
	iData->frameCounter += frames;

	if ( iData->frameCounter >= iData->totalFrames ) return 2;
		return 0;
}