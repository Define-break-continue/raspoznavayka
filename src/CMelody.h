//#include "aquila/aquila.h"
//#include "aquila/transform/FftFactory.h"

/*
 * _mel_size_t is a type to store length and offsets
 * of interval structures, representing melodies.
 */
typedef std::uint16_t _mel_size_t;

class CMelody {
    public:
    CMelody( std::vector< Aquila::SampleType > );
    CMelody( Aquila::WaveFile );
    CMelody( std::vector< _interval_t > intervals ) : intervals( intervals ) {}
    std::vector< _interval_t > getIntervals();
    _mel_size_t getLength();
    
    protected:
    std::vector< _interval_t > intervals;
    void setIntervals( Aquila::WaveFile );
};

