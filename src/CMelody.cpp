#include "CMelody.h"

CMelody::CMelody( std::vector< Aquila::SampleType >& waveform ) {
    setIntervals( waveform );
}

std::vector< Raspoznavayka::interval_t >& CMelody::getIntervals() {
    return intervals;
}

Raspoznavayka::mel_size_t CMelody::getLength() {
    return intervals.size();
}

void CMelody:setIntervals( std::vector< Aquila::SampleType >& ) {
    // TODO main code of physics part will be here
}
