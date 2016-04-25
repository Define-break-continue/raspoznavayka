namespace Raspoznavayka {
    // dB_t is used for storing and summing decibels. Every double can be converted to dB_t
    // dB_t += sth is arithmetic sum
    // dB_t = dB_t + sth, dB_t = sth + dB_t is logarithmic sum
    class dB_t {
    private:
        double data;
    public:
        dB_t( double x = std::numeric_limits< double >::min() ): data( x ) {}
        explicit operator double() const { return this->data; }
	dB_t& operator+=( const dB_t& a ) { this->data += a.data; return *this; }
	dB_t& operator+=( const double& a ) { this->data += a; return *this; }
	dB_t& operator-=( const dB_t& a ) { this->data -= a.data; return *this; }
	dB_t& operator-=( const double& a ) { this->data -= a; return *this; }
        friend const dB_t operator+( const dB_t& a, const dB_t& b );
        friend const dB_t operator+( const double& a, const dB_t& b );
        friend const dB_t operator-( const dB_t& a, const dB_t& b );
        friend const dB_t operator-( const double& a, const dB_t& b );
        friend const dB_t operator*( const double& a, const dB_t& b );
        friend const dB_t operator*( const dB_t& a, const double& b );
        friend const dB_t operator/( const dB_t& a, const double& b );
        friend ostream& operator<<( ostream& os, const dB_t& L );
    };
}

