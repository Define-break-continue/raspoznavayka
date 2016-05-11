#include "raspoznavayka.h"

const int CFixedHash::length = __FixedHashLength__;

CFixedHash::CFixedHash( const CHash& hash, Raspoznavayka::mel_size_t offset ) {
    std::vector< Raspoznavayka::arrow_t > parent_arrows = hash.getHash();
    std::vector< Raspoznavayka::arrow_t >::const_iterator beg = parent_arrows.begin() + offset;
    std::vector< Raspoznavayka::arrow_t >::const_iterator end = parent_arrows.begin() + offset + CFixedHash::length;
    assert( end <= parent_arrows.end() );
    this->setHash( std::vector< Raspoznavayka::arrow_t >( beg, end ) );
}

