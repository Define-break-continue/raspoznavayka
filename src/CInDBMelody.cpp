#include "raspoznavayka.h"

CInDBMelody::CInDBMelody( std::vector< Raspoznavayka::interval_t > intervals ) : CMelody( intervals ), idTag() {} // no honey - no money

CInDBMelody::CInDBMelody( CMelody& melody ) : CMelody( melody.getIntervals() ), idTag() {} // if no data => zero idTag

CInDBMelody::CInDBMelody( std::vector< Raspoznavayka::interval_t > intervals, CIDTag& idTag ) : CMelody( intervals ), idTag( idTag ) {}

CInDBMelody::CInDBMelody( CMelody& melody, CIDTag& idTag ) : CMelody( melody.getIntervals() ), idTag( idTag ) {}

CIDTag getIDTag();

CIDTag CInDBMelody::getIDTag() {
    return idTag;
}
