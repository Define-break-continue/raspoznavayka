//#include "CIDTag.h"

class CInDBMelody : CMelody {
public:
    CInDBMelody( std::vector< Raspoznavayka::interval_t > intervals ) : CMelody( intervals ), idTag() {} // no honey - no money
    CInDBMelody( CRecordedMelody& melody ) : CMelody( melody.getIntervals() ), idTag() {} // if no data => zero idTag
    CInDBMelody( std::vector< Raspoznavayka::interval_t > intervals, CIDTag& idTag ) : CMelody( intervals ), idTag( idTag ) {}
    CInDBMelody( CRecordedMelody& melody, CIDTag& idTag ) : CMelody( melody.getIntervals() ), idTag( idTag ) {}
    CIDTag getIDTag();
protected:
    CIDTag idTag;
};
