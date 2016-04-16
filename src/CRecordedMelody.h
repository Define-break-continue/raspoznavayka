#ifndef __RECORDED_MELODY_
#define __RECORDED_MELODY_

#include "raspoznavayka.h"
//#include "CMelody.h"
//#include "CHash.h"

class CRecordedMelody : public CMelody {
    public:
    CRecordedMelody( std::vector< Aquila::SampleType >& waveform ) : CMelody( waveform ), hash( 0 ) {}
    CRecordedMelody( std::vector< Raspoznavayka::interval_t >& intervals ) : CMelody( intervals ), hash( 0 ) {}
    CHash& getHash();

    protected:
    CHash hash;
    void setHash();
};

#endif // __RECORDED_MELODY_
