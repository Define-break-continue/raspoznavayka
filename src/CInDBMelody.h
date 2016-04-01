#include "CIDTag.h"

class CInDBMelody {
public:
    template< typename waveformType, typename ... idParams >
    CRecordedMelody( waveformType waveform ) : CMelody( waveform ), idTag( idParams ) {} // хз, будет ли работать, но попробовать стоит

protected:
    CIDTag idTag;
};

