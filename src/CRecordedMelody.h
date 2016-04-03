#ifndef __RECORDED_MELODY_
#define __RECORDED_MELODY_

#include "CMelody.h"
#include "CHash.h"

class CRecordedMelody : public CMelody {
    public:
    CRecordedMelody( std::vector< double > waveform ) : CMelody( waveform ), hash( 0 ) {}
    CRecordedMelody( std::vector< Aquila::SampleType > waveform ) : CMelody( waveform ), hash( 0 ) {}
    CRecordedMelody( Aquila::WaveType waveform ) : CMelody( waveform ), hash( 0 ) {}
    CHash getHash();

    protected:
    CHash hash;
    void setHash( Aquila::WaveType waveform );
};

#endif // __RECORDED_MELODY_
