#define __FixedHashLength__ 8

class CFixedHash : public CHash {
public:
    const static int length;
    CFixedHash( const CHash&, Raspoznavayka::mel_size_t offset );
};

