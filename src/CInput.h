#include "RtAudio.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "spline.h"

#include<fstream>
#include<string.h>

typedef double MY_TYPE;
#define FORMAT RTAUDIO_FLOAT64

#define DEFAULT_SAMPLE_RATE 11025


// Platform-dependent sleep routines.
#if defined( __WINDOWS_ASIO__ ) || defined( __WINDOWS_DS__ ) || defined( __WINDOWS_WASAPI__ )
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif


//struct InputData;	

class CInput {
	public:
		CInput();
		~CInput();
		std::vector<MY_TYPE> RecordMelody();
		
		struct InputData;
		MY_TYPE* Rediscretization(MY_TYPE* recording, double time, int sampleRateOfRecord);
		MY_TYPE* Decimation(MY_TYPE* recording, double time, int sampleRateOfRecord, int sampleRateNeeded);
		
		void StereoToMono(MY_TYPE* recording, MY_TYPE* buffer, unsigned long& sizeOfRecord, short channels);
	
		bool WithCorrectSampleRate();
	private:
		unsigned int inputSampleRate;
		std::vector<MY_TYPE> recordedMelody;
		
};

int Input( void * /*outputBuffer*/, void *inputBuffer, unsigned int nBufferFrames,
           double /*streamTime*/, RtAudioStreamStatus /*status*/, void *data );
