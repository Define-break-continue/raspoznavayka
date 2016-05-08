#include "raspoznavayka.h"

namespace Raspoznavayka {

    note_t& operator++( note_t& n ) {
        return n = static_cast< note_t >( static_cast< std::uint8_t >( n ) + 1 );
    }

    note_t operator+( const note_t& a, const int& b ) {
        return static_cast< note_t >( static_cast< std::uint8_t >( a ) + b );
    }

    note_t operator+( const note_t& a, const std::size_t& b ) {
        return static_cast< note_t >( static_cast< std::uint8_t >( a ) + b );
    }

    interval_t operator-( const note_t& a, const note_t& b ) {
        return static_cast< interval_t >( static_cast< std::uint8_t >( a ) - static_cast< std::uint8_t >( b ) );
    }

    interval_t& operator++( interval_t& n ) {
        return n = static_cast< interval_t >( static_cast< std::uint8_t >( n ) + 1 );
    }

    interval_t operator+( const interval_t& a, const int& b ) {
        return static_cast< interval_t >( static_cast< std::uint8_t >( a ) + b );
    }

    interval_t operator+( const interval_t& a, const std::size_t& b ) {
        return static_cast< interval_t >( static_cast< std::uint8_t >( a ) + b );
    }

}
