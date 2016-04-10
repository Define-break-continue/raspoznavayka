namespace Raspoznavayka {
    typedef std::int8_t arrow_t;
    typedef arrow_t ArrowType;
}

#define _arrow_up 1
#define _arrow_equal 0
#define _arrow_down -1

class CHash {
public:
    CHash();
    template< typename CGeneralMelody >
        CHash( const CGeneralMelody& ); // CHash constructor for all Melody classes
    CHash( std::vector< Raspoznavayka::interval_t > );
    CHash getHash();
    Raspoznavayka::MelodySizeType getLength();
protected:
    void setHash( std::vector< Raspoznavayka::interval_t > );
    std::vector< Raspoznavayka::arrow_t > arrows;
};

