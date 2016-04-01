#ifndef __HASH_
#define __HASH_

#include <vector>
#include "interval_t.h"
#include "raspoznavayka.h"

/*  
 * arrow_t == -1 || 1 || 0
 *
*/

typedef std::int8_t arrow_t;

class CHash {
    public:
    CHash();
    CHash( std::vector< interval_t > intervals );
    CHash getHash();
    _mel_size_t getLength();
    protected:
    void setHash( std::vector< interval_t > intervals );
    std::vector< arrow_t > arrows;
};

#endif // __HASH_
