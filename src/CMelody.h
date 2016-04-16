//#include "lib/aquila/aquila.h"
//#include "lib/aquila/transform/FftFactory.h"

/*
 * Raspoznavayka::mel_size_t is a type to store length and offsets
 * of interval structures, representing melodies.
 */

namespace Raspoznavayka {
    typedef std::uint16_t mel_size_t;
    typedef mel_size_t MelodySizeType;
}

class CMelody {
    public:
    CMelody( std::vector< Aquila::SampleType > );
    CMelody( Aquila::WaveFile );
    CMelody( std::vector< Raspoznavayka::interval_t > intervals ) : intervals( intervals ) {}
    std::vector< Raspoznavayka::interval_t > getIntervals();
    Raspoznavayka::mel_size_t getLength();
    
    protected:
    std::vector< Raspoznavayka::interval_t > intervals;
    void setIntervals( Aquila::WaveFile );
};

