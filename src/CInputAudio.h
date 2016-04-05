#ifndef __INPUT_AUDIO_
#define __INPUT_AUDIO_

#include "raspoznavayka.h"

class CInputAudio {
    public:
    CInputAudio( std::string /*fileDest = "test.wav"*/ );
    std::vector< Aquila::SampleType > getSignal();
    void ReadAudioHelper( std::string );
    protected:
    std::vector< Aquila::SampleType > signal;
};

#endif // __INPUT_AUDIO_
