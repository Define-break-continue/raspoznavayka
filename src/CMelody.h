/*
 * Raspoznavayka::mel_size_t is a type to store length and offsets
 * of interval structures, representing melodies.
 */

namespace Raspoznavayka {
    typedef std::uint32_t mel_size_t;
    typedef mel_size_t MelodySizeType;
}

class CMelody {
    public:
    CMelody( std::vector< Aquila::SampleType >& );
    CMelody( const std::vector< Raspoznavayka::interval_t >& intervals );
    const std::vector< Raspoznavayka::interval_t >& getIntervals() const;
    Raspoznavayka::mel_size_t getLength() const;
    void printIntervals();
    
    protected:
    std::vector< Raspoznavayka::interval_t > intervals;
    void setIntervals( std::vector< Aquila::SampleType >& );
};
