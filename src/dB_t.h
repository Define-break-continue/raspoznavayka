namespace Raspoznavayka {
    // dB_t is used for storing and summing decibels. Every double can be converted to dB_t
    // dB_t % | << sth is arithmetic sum, >> is arithmetic residual
    class dB_t {
    public:
        dB_t( double x = std::numeric_limits< double >::min() );
        explicit operator double() const;
        const dB_t& operator+=( const dB_t& a );
        const dB_t& operator+=( const double& a );
        const dB_t& operator-=( const dB_t& a );
        const dB_t& operator-=( const double& a );
        const dB_t& operator%=( const dB_t& a );
        const dB_t& operator%=( const double& a );
        const dB_t& operator<<=( const dB_t& a );
        const dB_t& operator<<=( const double& a );
        const dB_t& operator>>=( const dB_t& a );
        const dB_t& operator>>=( const double& a );
        const dB_t& operator*=( const double& a );
        const dB_t& operator/=( const double& a );
        const dB_t& operator++();
        const dB_t operator++( int );
        const dB_t& operator--();
        const dB_t operator--( int );
        friend const dB_t operator+( const dB_t& a, const dB_t& b );
        friend const dB_t operator+( const double& a, const dB_t& b );
        friend const dB_t operator-( const dB_t& a, const dB_t& b );
        friend const dB_t operator-( const double& a, const dB_t& b );
        friend const dB_t operator%( const dB_t& a, const dB_t& b );
        friend const dB_t operator%( const double& a, const dB_t& b );
        friend const dB_t operator<<( const dB_t& a, const dB_t& b );
        friend const dB_t operator<<( const double& a, const dB_t& b );
        friend const dB_t operator>>( const dB_t& a, const dB_t& b );
        friend const dB_t operator>>( const double& a, const dB_t& b );
        friend const dB_t operator*( const double& a, const dB_t& b );
        friend const dB_t operator*( const dB_t& a, const double& b );
        friend const dB_t operator/( const dB_t& a, const double& b );
        friend const bool operator==( const double& a, const dB_t& b );
        friend const bool operator!=( const double& a, const dB_t& b );
        friend const bool operator>=( const double& a, const dB_t& b );
        friend const bool operator<=( const double& a, const dB_t& b );
        friend const bool operator>( const double& a, const dB_t& b );
        friend const bool operator<( const double& a, const dB_t& b );
        friend const bool operator==( const dB_t& a, const dB_t& b );
        friend const bool operator!=( const dB_t& a, const dB_t& b );
        friend const bool operator>=( const dB_t& a, const dB_t& b );
        friend const bool operator<=( const dB_t& a, const dB_t& b );
        friend const bool operator>( const dB_t& a, const dB_t& b );
        friend const bool operator<( const dB_t& a, const dB_t& b );
        friend const dB_t rms2( const dB_t& a, const dB_t& b );
        friend const dB_t rms2( const double& a, const dB_t& b );
        friend const dB_t rms2( const dB_t& a, const double& b );
        friend const double abs( const dB_t& );
        friend const dB_t sqrt( const dB_t& );
        friend std::ostream& operator<<( std::ostream& os, const dB_t& L );
        static const double min();
        static const double max();
    private:
        double data;
    };
}

