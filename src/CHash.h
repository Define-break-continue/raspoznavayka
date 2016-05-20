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
    CHash( const std::vector< Raspoznavayka::interval_t >& );
    CHash( const CMelody& melody );
    const std::vector< Raspoznavayka::arrow_t >& getHash() const;
    Raspoznavayka::mel_size_t getLength() const;
protected:
    void setHash( const std::vector< Raspoznavayka::interval_t >& );
    void setHash( const std::vector< Raspoznavayka::arrow_t >& );
    std::vector< Raspoznavayka::arrow_t > arrows;
};

