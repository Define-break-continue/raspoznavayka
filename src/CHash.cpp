#include "CHash.h"
#include "CMelody.h"

CHash::CHash() : arrows( 0 ) {}

CHash::CHash( std::vector< Raspoznavayka::interval_t > intervals ) {
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

std::vector< Raspoznavayka::arrow_t > CHash::getHash() {
    return arrows;
}

Raspoznavayka::arrow_t sg( Raspoznavayka::interval_t x ) {
    return ( x > 0 ) ? 1 : ( ( x < 0 ) ? -1 : 0 );
}

void CHash::setHash( std::vector< Raspoznavayka::interval_t > intervals ) {
    for ( std::size_t i = 0; i < intervals.size(); ++i ) {
        arrows[ i ] = sg( intervals[i] );
    }
}

Raspoznavayka::mel_size_t CHash::getLength() {
    return arrows.size();
}
