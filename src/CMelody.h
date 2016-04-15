#ifndef __MELODY_
#define __MELODY_

#include "raspoznavayka.h"

//#include "aquila/aquila.h"
//#include "aquila/transform/FftFactory.h"

/*
 * Raspoznavayka::mel_size_t is a type to store length and offsets
 * of interval structures, representing melodies.
 */

namespace Raspoznavayka {
    typedef std::uint16_t mel_size_t;
    typedef std::uint16_t MelodySizeType;
    typedef std::vector< std::vector < double > > Spectrogram;
}

class CMelody {
    public:
    CMelody( std::vector< Aquila::SampleType >& );
    CMelody( std::vector< Raspoznavayka::interval_t >& intervals ) : intervals( intervals ) {}
    std::vector< Raspoznavayka::interval_t >& getIntervals();
    Raspoznavayka::mel_size_t getLength();
    
    protected:
    std::vector< Raspoznavayka::interval_t > intervals;
    void setIntervals( std::vector< Aquila::SampleType >& );
};

#endif // __MELODY_
