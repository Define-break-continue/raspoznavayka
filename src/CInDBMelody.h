#include "CIDTag.h"

class CInDBMelody : public CMelody {
public:
    template< typename waveformType, typename ... idParams >
    CInDBMelody( waveformType waveform ) : CMelody( waveform ), idTag( idParams ) {} // хз, будет ли работать, но попробовать стоит
    CInDBMelody( std::vector< _interval_t > intervals,
                 std::string artist,
                 std::string album,
                 std::string title,
                 uint8_t year );
protected:
    CIDTag idTag;
};

