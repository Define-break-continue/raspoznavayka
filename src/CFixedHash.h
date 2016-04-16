#include "raspoznavayka.h"

class CFixedHash : public CHash {
public:
    static int length;
    CFixedHash( const CHash&, Raspoznavayka::mel_size_t offset );
};

