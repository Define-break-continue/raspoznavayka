typedef std::int8_t _arrow_t;

#define _arrow_up 1
#define _arrow_equal 0
#define _arrow_down -1

class CHash {
public:
    CHash();
    CHash( std::vector< interval_t > intervals );
    CHash getHash();
    _mel_size_t getLength();
protected:
    void setHash( std::vector< interval_t > intervals );
    std::vector< _arrow_t > arrows;
};

