#include "raspoznavayka.h"

namespace Raspoznavayka {
    inline double dBSum( const double& a, const double& b );
    inline double dBResidual( const double& a, const double& b );
    inline double dBDifference( const double& a, const double& b );

    const dB_t operator+( const dB_t& a, const dB_t& b ) { 
        return dB_t( 10 * log10( pow( 10, a.data / 10 ) + pow( 10, b.data / 10 ) ) );
    }
    
    const dB_t operator+( const double& a, const dB_t& b ) { 
        return dB_t( 10 * log10( pow( 10, a / 10 ) + pow( 10, b.data / 10 ) ) );
    }

    const dB_t operator-( const dB_t& a, const dB_t& b ) { 
        return dB_t( 10 * log10( pow( 10, a.data / 10 ) - pow( 10, b.data / 10 ) ) );
    }
    
    const dB_t operator-( const double& a, const dB_t& b ) { 
        return dB_t( 10 * log10( pow( 10, a / 10 ) - pow( 10, b.data / 10 ) ) );
    }

    const dB_t operator%( const dB_t& a, const dB_t& b ) { 
        return rms2( a, b );
    }
    
    const dB_t operator%( const double& a, const dB_t& b ) { 
        return rms2( a, b );
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

    const bool operator!=( const double& a, const dB_t& b ) {
        return a != b.data;
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

    const bool operator!=( const dB_t& a, const dB_t& b ) {
        return a.data != b.data;
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
    
    std::ostream& operator<<( std::ostream& os, const dB_t& a ) { 
        os << a.data;
        return os; 
    }

    dB_t::dB_t( double x ): data( x ) { }

    dB_t::operator double() const {
        return this->data; 
    }

    const dB_t& dB_t::operator+=( const dB_t& a ) {
        return *this = *this + a;
    }

    const dB_t& dB_t::operator+=( const double& a ) {
        return *this = *this + a;
    }

    const dB_t& dB_t::operator-=( const dB_t& a ) {
        return *this = *this - a;
    }

    const dB_t& dB_t::operator-=( const double& a ) {
        return *this = *this - a;
    }

    const dB_t& dB_t::operator%=( const dB_t& a ) {
        return *this = rms2( *this, a );
    }

    const dB_t& dB_t::operator%=( const double& a ) {
        return *this = rms2( *this, a );
    }

    const dB_t& dB_t::operator<<=( const dB_t& a ) {
        this->data += a.data; return *this; 
    }

    const dB_t& dB_t::operator<<=( const double& a ) {
        this->data += a; return *this; 
    }

    const dB_t& dB_t::operator>>=( const dB_t& a ) {
        this->data -= a.data; return *this; 
    }

    const dB_t& dB_t::operator>>=( const double& a ) {
        this->data -= a; return *this; 
    }

    const dB_t& dB_t::operator*=( const double& a ) {
        this->data *= a; return *this;
    }

    const dB_t& dB_t::operator/=( const double& a ) {
        this->data /= a; return *this;
    }

    const dB_t& dB_t::operator++() {
        this->data += 1; return *this; 
    }

    const dB_t dB_t::operator++( int ) {
        auto temp = *this; this->data += 1; return temp; 
    }

    const dB_t& dB_t::operator--() {
        this->data -= 1; return *this; 
    }

    const dB_t dB_t::operator--( int ) {
        auto temp = *this; this->data -= 1; return temp; 
    }

    const dB_t rms2( const dB_t& a, const dB_t& b ) {
        return dB_t( 10 * log10( ( pow( 10, a.data / 10 ) + pow( 10, b.data / 10 ) ) / 2 ) );
    }

    const dB_t rms2( const double& a, const dB_t& b ) {
        return dB_t( 10 * log10( ( pow( 10, a / 10 ) + pow( 10, b.data / 10 ) ) / 2 ) );
    }

    const dB_t rms2( const dB_t& a, const double& b ) {
        return dB_t( 10 * log10( ( pow( 10, a.data / 10 ) + pow( 10, b / 10 ) ) / 2 ) );
    }

    const double abs( const dB_t& a ) {
        return a > 0 ? a.data : -a.data;
    }

    const dB_t sqrt( const dB_t& a ) {
        return dB_t( sqrt( a.data ) );
    }

    const double dB_t::min() {
        return -std::numeric_limits< double >::max(); 
    }

    const double dB_t::max() {
        return std::numeric_limits< double >::max(); 
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
