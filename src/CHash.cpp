#include "CHash.h"
#include "CMelody.h"

CHash::CHash() : arrows( 0 ) {}

CHash::CHash( std::vector< interval_t > intervals ) {
    arrows( intervals.size() );
    setHash( intervals );
}

template< typename CGeneralMelody >
CHash::CHash( const CGeneralMelody& melody ) {
    arrows( melody.getLength() );
    setHash( melody.getIntervals() );
}

CHash::CHash( const CMelody& melody ) {
    arrows( melody.getLength() );
    setHash( melody.getIntervals() );
}

~CHash() {}

std::vector< arrow_t > CHash::getHash() {
    return arrows;
}

_arrow_t sg( _interval_t x ) {
    return ( x > 0 ) ? 1 : ( ( x < 0 ) ? -1 : 0 );
}

void CHash::setHash( std::vector< interval_t > intervals ) {
    for ( std::size_t i = 0; i < intervals.size(); ++i ) {
        arrows[ i ] = sg( intervals[i] );
    }
}

_mel_size_t CHash::getLength() {
    return arrows.size();
}
