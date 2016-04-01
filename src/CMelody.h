#ifndef __MELODY_
#define __MELODY_

#include <iostream>
#include <string>
#include <vector>
#include "aquila/aquila.h"
#include "aquila/transform/FftFactory.h"

#include "interval_t.h"
#include "raspoznavayka.h"

class CMelody {
    public:
    CMelody( std::vector< double > waveform );
    CMelody( std::vector< Aquila::SampleType > waveform );
    CMelody( Aquila::WaveType waveform );
    std::vector< interval_t > getIntervals();
    _mel_size_t getLength();
    
    protected:
    std::vector< interval_t > intervals;
    void setIntervals( Aquila::WaveType waveform );
};

#endif // __MELODY_
