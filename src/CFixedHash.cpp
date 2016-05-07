CFixedHash::CFixedHash( const CHash&, Raspoznavayka::mel_size_t offset ) {
    std::vector< Raspoznavayka::arrow_t > parent_arrows = CHash.getHash();
    std::vector< Raspoznavayka::arrow_t >::const_iterator beg = parent_arrows.begin() + offset;
    std::vector< Raspoznavayka::arrow_t >::const_iterator end = parent_arrows.end() + offset + CFixedHash::length;
    setHash( std::vector< Raspoznavayka::arrow_t >( beg, end ) );
}

