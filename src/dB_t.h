namespace Raspoznavayka {
    // dB_t is used for storing and summing decibels. Every double can be converted to dB_t
    // dB_t % | << sth is arithmetic sum, >> is arithmetic residual
    class dB_t {
    private:
        double data;
    public:
        dB_t( double x = std::numeric_limits< double >::min() ): data( x ) {}
        explicit operator double() const { return this->data; }
	const dB_t& operator+=( const dB_t& a ) { this->data += a.data; return *this; }
	const dB_t& operator+=( const double& a ) { this->data += a; return *this; }
	const dB_t& operator-=( const dB_t& a ) { this->data -= a.data; return *this; }
	const dB_t& operator-=( const double& a ) { this->data -= a; return *this; }
	const dB_t& operator%=( const dB_t& a ) { this->data += a.data; return *this; }
	const dB_t& operator%=( const double& a ) { this->data += a; return *this; }
        const dB_t& operator<<=( const dB_t& a ) { this->data += a.data; return *this; }
        const dB_t& operator<<=( const double& a ) { this->data += a; return *this; }
        const dB_t& operator>>=( const dB_t& a ) { this->data -= a.data; return *this; }
        const dB_t& operator>>=( const double& a ) { this->data -= a; return *this; }
	const dB_t& operator++() { this->data += 1; return *this; }
	const dB_t operator++( int ) { auto temp = *this; this->data += 1; return temp; }
	const dB_t& operator--() { this->data -= 1; return *this; }
	const dB_t operator--( int ) { auto temp = *this; this->data -= 1; return temp; }
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
	friend const bool operator>=( const double& a, const dB_t& b );
	friend const bool operator<=( const double& a, const dB_t& b );
	friend const bool operator>( const double& a, const dB_t& b );
	friend const bool operator<( const double& a, const dB_t& b );
	friend const bool operator==( const dB_t& a, const dB_t& b );
	friend const bool operator>=( const dB_t& a, const dB_t& b );
	friend const bool operator<=( const dB_t& a, const dB_t& b );
	friend const bool operator>( const dB_t& a, const dB_t& b );
        friend const bool operator<( const dB_t& a, const dB_t& b );
        friend std::ostream& operator<<( std::ostream& os, const dB_t& L );
	static const double min() { return std::numeric_limits< double >::min(); }
	static const double max() { return std::numeric_limits< double >::max(); }
    };
}

