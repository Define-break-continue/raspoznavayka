#include "raspoznavayka.h"

CRecordedMelody::CRecordedMelody( std::vector< Aquila::SampleType >& waveform ) : CMelody( waveform ) {
    hash = CHash( getIntervals() );
}
    

CRecordedMelody::CRecordedMelody( std::vector< Raspoznavayka::interval_t >& intervals ) : CMelody( intervals ) {
    hash = CHash( intervals );
}

const CHash& CRecordedMelody::getHash() const {
    return hash;
}

