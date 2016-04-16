#include "CInputAudio.h"

CInputAudio::CInputAudio( std::string fileDest ) : signal( 0 ) { 
    ReadAudioHelper( fileDest );
}

std::vector< Aquila::SampleType > CInputAudio::getSignal() {
    return signal;
}

void CInputAudio::ReadAudioHelper( std::string fileDest ) {
    Aquila::WaveFile wav( fileDest );
    std::cout << "Loaded file: " << wav.getFilename()
              << " (" << wav.getBitsPerSample() << "b)" << std::endl;

    signal.resize( wav.getSamplesCount() );
    auto signalIterator = 0;
    for (auto sample : wav) {
        signal[ signalIterator++ ] = sample;
    }   
}

// change sample rate. The objective frequency is staged in raspoznavayka.h defines
// void CInputAudio::Resample(/**/ ) {
//     int k = fs / SAMPLE_RATE;
//     if( k == 1 ) return;
//     if( k > 1 ) {
//         // decimation
//     } else {
//         // upsampling
//     }
// }
