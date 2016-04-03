#include "chash.h"
#include "cmelody.h"

CHash::CHash() : arrows( 0 ) {}

CHash::CHash( std::vector< interval_t > intervals ) {
    arrows( intervals.size() );
    setHash( intervals );
}

~CHash() {}

std::vector< arrow_t > CHash::getHash() {
    return arrows;
}

arrow_t sg( auto x ) {
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
