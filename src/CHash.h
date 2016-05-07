namespace Raspoznavayka {
    typedef std::int8_t arrow_t;
    typedef arrow_t ArrowType;
    const std::int8_t arrow_up = 1;
    const std::int8_t arrow_equal = 0;
    const std::int8_t arrow_down = -1;
}

class CHash {
public:
    CHash();
    /*
     * A hash can be made of a CMelody or an vector< interval_t >
     * If a template is needed, it should be done in CMelody,
     * or  as a template vector< interval_t > function
     * So this one is unnecessary
    template< typename CGeneralMelody >
        CHash( const CGeneralMelody& ); // CHash constructor for all Melody classes
    */
    CHash( const std::vector< Raspoznavayka::interval_t >& );
    CHash( const CMelody& melody );
    const std::vector< Raspoznavayka::arrow_t >& getHash() const;
    Raspoznavayka::mel_size_t getLength() const;
protected:
    void setHash( const std::vector< Raspoznavayka::interval_t >& );
    void setHash( const std::vector< Raspoznavayka::arrow_t >& );
    std::vector< Raspoznavayka::arrow_t > arrows;
};

