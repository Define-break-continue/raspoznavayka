#include "raspoznavayka.h"

namespace Raspoznavayka {
    inline double dBSum( const double& a, const double& b );
    inline double dBResidual( const double& a, const double& b );
    inline double dBDifference( const double& a, const double& b );

    const dB_t operator+( const dB_t& a, const dB_t& b ) { 
        return dB_t( dBSum( a.data, b.data ) );
    }
    
    const dB_t operator+( const double& a, const dB_t& b ) { 
        return dB_t( dBSum( a, b.data ) );
    }

    const dB_t operator%( const dB_t& a, const dB_t& b ) { 
        return dB_t( a.data + b.data );
    }
    
    const dB_t operator%( const double& a, const dB_t& b ) { 
        return dB_t( a + b.data );
    }
    
    const dB_t operator<<( const dB_t& a, const dB_t& b ) {
        return dB_t( a.data + b.data );
    }

    const dB_t operator<<( const double& a, const dB_t& b ) {
        return dB_t( a + b.data );
    }

    const dB_t operator>>( const dB_t& a, const dB_t& b ) {
        return dB_t( a.data - b.data );
    }

    const dB_t operator>>( const double& a, const dB_t& b ) {
        return dB_t( a - b.data );
    }

    const dB_t operator*( const double& a, const dB_t& b ) {
        return dB_t( a * b.data );
    }

    const dB_t operator*( const dB_t& a, const double& b ) {
        return dB_t( b * a.data );
    }

    const dB_t operator/( const dB_t& a, const double& b ) {
        return dB_t( a.data / b );
    }

    const bool operator==( const double& a, const dB_t& b ) {
        return a == b.data;
    }

    const bool operator>=( const double& a, const dB_t& b ) {
        return a >= b.data;
    }

    const bool operator<=( const double& a, const dB_t& b ) {
        return a <= b.data;
    }

    const bool operator>( const double& a, const dB_t& b ) {
        return a > b.data;
    }

    const bool operator<( const double& a, const dB_t& b ) {
        return a < b.data;
    }

    const bool operator==( const dB_t& a, const dB_t& b ) {
        return a.data == b.data;
    }

    const bool operator>=( const dB_t& a, const dB_t& b ) {
        return a.data >= b.data;
    }

    const bool operator<=( const dB_t& a, const dB_t& b ) {
        return a.data <= b.data;
    }

    const bool operator>( const dB_t& a, const dB_t& b ) {
        return a.data > b.data;
    }

    const bool operator<( const dB_t& a, const dB_t& b ) {
        return a.data < b.data;
    }
    
    ostream& operator<<( ostream& os, const dB_t& a ) { 
        os << a.data;
        return os; 
    }

    inline double dBSum( const double& a, const double& b ) {
        double max = std::max( a, b );
        double min = std::min( a, b );
	return max + dBDifference( max, min );
    }

    inline double dBResidual( const double& a, const double& b ) {
        if( b > a ) return std::numeric_limits< double >::min();
	if( b < 0 ) return dBSum( a, -b );
        return a - dBDifference( a, b );
    }

    inline double dBDifference( const double& a, const double& b ) {
        switch( int( std::round( a - b ) ) ) {
            case 0: return 3;
            case 1: return 2.5;
            case 2:
            case 3: return 2;
            case 4: return 1.5;
            case 5:
            case 6:
            case 7: return 1;
            case 8:
            case 9: return 0.5;
        }
        return 0;
    }
}
