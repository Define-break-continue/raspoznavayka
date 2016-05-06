//#include "CIDTag.h"

class CInDBMelody : public CMelody {
public:
    CInDBMelody( std::vector< Raspoznavayka::interval_t > intervals );
    CInDBMelody( CRecordedMelody& melody );
    CInDBMelody( std::vector< Raspoznavayka::interval_t > intervals, CIDTag& idTag );
    CInDBMelody( CRecordedMelody& melody, CIDTag& idTag );
    CIDTag getIDTag();
protected:
    CIDTag idTag;
};
