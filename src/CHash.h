#include "raspoznavayka.h"
#include "CMelody.h"

namespace Raspoznavayka {
    typedef std::int8_t arrow_t;
    typedef arrow_t ArrowType;
    const std::int8_t arrow_up = 1;
    const std::int8_t arrow_equal = 0;
    const std::int8_t arrow_down = -1;
}

class CHash {
public:
    CHash();
    template< typename CGeneralMelody >
        CHash( const CGeneralMelody& ); // CHash constructor for all Melody classes
    CHash( std::vector< Raspoznavayka::interval_t >& );
    std::vector< Raspoznavayka::arrow_t >& getHash();
    Raspoznavayka::mel_size_t getLength();
protected:
    void setHash( std::vector< Raspoznavayka::interval_t >& );
    std::vector< Raspoznavayka::arrow_t > arrows;
};

