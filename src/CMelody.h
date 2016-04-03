//#include "aquila/aquila.h"
//#include "aquila/transform/FftFactory.h"

/*
 * _mel_size_t is a type to store length and offsets
 * of interval structures, representing melodies.
 */
#define _mel_size_t uint16_t

class CMelody {
    public:
    CMelody( std::vector< double > waveform );
//    CMelody( std::vector< Aquila::SampleType > waveform );
//    CMelody( Aquila::WaveType waveform );
    std::vector< _interval_t > getIntervals();
    _mel_size_t getLength();
    
    protected:
    std::vector< _interval_t > intervals;
//    void setIntervals( Aquila::WaveType waveform );
};

