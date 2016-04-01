#ifndef __IN_DB_MELODY_
#define __IN_DB_MELODY_

#include "CMelody.h"
#include "CIDTag.h"

class CInDBMelody {
    public:
    template< typename waveformType, typename ... idParams >
    CRecordedMelody( waveformType waveform ) : CMelody( waveform ), idTag( idParams ) {} // хз, будет ли работать, но попробовать стоит

    protected:
    CIDTag idTag;
};

#endif // __IN_DB_MELODY_
