#include "raspoznavayka.h"

namespace Raspoznavayka {

    note_t& operator++( note_t& n ) {
        return n = static_cast< note_t >( static_cast< std::uint8_t >( n ) + 1 );
    }

    interval_t operator-( const note_t& a, const note_t& b ) {
        return static_cast< interval_t >( static_cast< std::uint8_t >( a ) - static_cast< std::uint8_t >( b ) );
    }

}
