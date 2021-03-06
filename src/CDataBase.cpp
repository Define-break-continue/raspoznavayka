#include "raspoznavayka.h"

const CDataBase& CDataBase::getInstance() {
    static CDataBase theSingleInstance;
    return theSingleInstance;
}

CDataBase::CDataBase() {
    /* 
     * This will be read from a .config file at runtime
     * when CDataBase.getInstance is first time called...
     */
    directory = "database";
#ifdef __NIX__
    index_filename = directory + '/' + "index";
    id3_filename = directory + '/' + "id3_tags";
    mel_filename = directory + '/' + "melodies";
    hash_file_subdir = directory + '/' + "hashes" + '/';
#elif __WIN__
    index_filename = directory + '\\' + "index";
    id3_filename = directory + '\\' + "id3_tags";
    mel_filename = directory + '\\' + "melodies";
    hash_file_subdir = directory + '\\' + "hashes" + '\\';
#else 
#error Set either __NIX__ or __WIN__
#endif
    id3_file_max_size_koeff = 4; // number of bytes in index file to store offsets of id3's by index
    mel_file_max_size_koeff = 4; // number of bytes in index file to store offsets of melodies by index
    mel_max_size_koeff = 2; // number of bytes to store a hash match offset of a melody for a hash
                            // this koeff should be less or (better) equal to Raspoznavayka::mel_size_t
    assert( sizeof( mel_max_size_koeff ) <= sizeof( Raspoznavayka::mel_size_t ) );
    mel_number_size_koeff = 4; // number of bytes to store a melody's index
    hash_file_extension = std::string( ".hash" );
    /*
     * ... till here
     * a database is shipped with its .config and both
     * are platform-independent
     */
    check_create_directory( directory.c_str() );
    check_create_directory( hash_file_subdir.c_str() );
}

bool CDataBase::addMelody( CInDBMelody melody ) const {
    std::ofstream id3_file;
    std::ofstream mel_file;
    std::ofstream index_file;
    index_file.open( index_filename, std::fstream::out | std::fstream::app );

    // check if index file is empty
    if( index_file.tellp() == 0 ) {
        // if index file is empty, write initial zeros as the first entry address
        for( int i = 0; i < id3_file_max_size_koeff + mel_file_max_size_koeff; ++i ) {
            index_file.write( "\0", 1 );
        }
        // and reset the other files
        mel_file.open( mel_filename, std::fstream::out | std::fstream::trunc | std::fstream::binary );
        id3_file.open( id3_filename, std::fstream::out | std::fstream::trunc | std::fstream::binary );
    }
    else {
        // index is not empty, append to files
        mel_file.open( mel_filename, std::fstream::out | std::fstream::app | std::fstream::binary );
        id3_file.open( id3_filename, std::fstream::out | std::fstream::app | std::fstream::binary );
    }
    if( ! ( id3_file.is_open() && mel_file.is_open() && index_file.is_open() ) ) {
        std::cout << "ERROR: Couldn't open some DB file for writing in " << directory << '\n';
        return false;
    }

    // write melody
    std::vector< Raspoznavayka::interval_t > mel_intervals = melody.getIntervals();
    Raspoznavayka::mel_size_t mel_size = mel_intervals.size();
    char *mel_char_intervals = new char[mel_size];
    for( std::vector< Raspoznavayka::interval_t >::size_type i = 0; i < mel_size; ++i ) {
        mel_char_intervals[i] = mel_intervals[i];
    }
    mel_file.write( mel_char_intervals, mel_size );
    delete mel_char_intervals;

    CIDTag idtag = melody.getIDTag();
    id3_file << idtag.artist << '\n' << idtag.album << '\n' << idtag.title << '\n' << idtag.year << '\n';

    // get positions at id3 and melody files, store
    // them in index file
    std::streampos pos = id3_file.tellp();
    for( int i = 0; i < id3_file_max_size_koeff; ++i ) {
        index_file.write( ((char*)&pos) + id3_file_max_size_koeff - i - 1, 1 );
    }
    pos = mel_file.tellp();
    for( int i = 0; i < mel_file_max_size_koeff; ++i ) {
        index_file.write( ((char*)&pos) + mel_file_max_size_koeff - i - 1, 1 );
    }
    // make pos = index of the song currently being added
    pos = index_file.tellp() / ( mel_file_max_size_koeff + id3_file_max_size_koeff );
    pos -= 2;
    id3_file.close();
    mel_file.close();
    index_file.close();

    // iterate through the song's FixedHashes
    CHash hash( melody );
    for( Raspoznavayka::mel_size_t offset = 0; offset < mel_size - CFixedHash::length; ++offset ) {
        CFixedHash fixed_hash( hash, offset );
        // open the appropriate hash file to write current fixed hash match to 
        std::ofstream hash_file;
        std::string hash_filename = makeFilenameOfHash( fixed_hash );
        hash_file.open( makeFilenameOfHash( fixed_hash ),
                       std::fstream::out | std::fstream::app | std::fstream::binary );
        if( ! hash_file.is_open() ) {
            std::cout << "ERROR: Couldn't open hash file for writing: " << hash_filename << '\n';
            return false;
        }
        // write melody id
        for( int i = 0; i < mel_number_size_koeff; ++i ) {
            hash_file.write( ((char*)&pos) + mel_number_size_koeff - i - 1, 1 );
        }
        // write fixed hash match offset
        uint64_t offset_64b = offset;
        for( int i = 0; i < mel_max_size_koeff; ++i ) {
            hash_file.write( ((char*)&offset_64b) + mel_max_size_koeff - i - 1, 1 );
        }
        hash_file.close();
    }
    return true;
}

std::vector< CInDBMelody > CDataBase::searchByHash( CHash hash ) const {
    std::vector< CInDBMelody > result;
    std::ifstream hash_file;
    std::vector< uint64_t > matches; // vector of mel_id

    // hash offset cycle
    for( int64_t fixed_hash_offset = 0; fixed_hash_offset < hash.getLength() - static_cast< int64_t >( CFixedHash::length ); 
            ++fixed_hash_offset ) {

        CFixedHash fixed_hash( hash, fixed_hash_offset );
        std::string hash_filename = makeFilenameOfHash( fixed_hash );
        hash_file.open( makeFilenameOfHash( fixed_hash ),
                        std::fstream::in | std::fstream::binary );
        if( ! hash_file.is_open() ) {
            std::cout << "ERROR: Couldn't open hash file for reading: " << hash_filename << '\n';
            return result;
        }

        // fixed hash file read cycle
        while( hash_file.is_open() && hash_file.good() && hash_file.peek() != EOF ) {
            uint64_t mel_id = 0;
            Raspoznavayka::mel_size_t mel_chm_offs = 0;
            if( ! ( read_number_from_file( mel_id, mel_number_size_koeff, hash_file ) // read melody id
                 && read_number_from_file( mel_chm_offs, mel_max_size_koeff, hash_file ) // read fixed hash match offset in melody
                 ) ) {
                return result;
            }
            
            // check distinct
            bool found = false;
            for( std::vector< uint64_t >::iterator i = matches.begin(); i != matches.end(); ++i ) {
                if( (*i) == mel_id ) {
                    found = true;
                    break;
                }
            }
            if( !found ) {
                // push to matches
                matches.push_back( mel_id );
            }
        } // end of fixed hash file read cycle

        hash_file.close();
    } // end of hash offset cycle

    // read found melodies' data
    std::ifstream index_file;
    std::ifstream id3_file;
    std::ifstream mel_file;
    index_file.open( index_filename, std::fstream::in | std::fstream::binary );
    id3_file.open( id3_filename, std::fstream::in );
    mel_file.open( mel_filename, std::fstream::in | std::fstream::binary );
    if( ! ( index_file.is_open() && id3_file.is_open() && mel_file.is_open() ) ) {
        std::cout << "ERROR: Couldn't open some DB file for reading in " << directory << '\n';
        return result;
    }

    for( std::vector< uint64_t >::iterator match = matches.begin(); match != matches.end(); ++match ) {
        int64_t mel_id = *match;
        // get index entry on this song
        index_file.seekg( mel_id * ( mel_number_size_koeff + mel_file_max_size_koeff ) );
        // get id3 and and melody addresses
        uint64_t id3_start = 0, id3_end = 0, mel_start = 0, mel_end = 0;
        if( ! ( read_number_from_file( id3_start, id3_file_max_size_koeff, index_file )
             && read_number_from_file( mel_start, mel_file_max_size_koeff, index_file )
             && read_number_from_file( id3_end, id3_file_max_size_koeff, index_file )
             && read_number_from_file( mel_end, mel_file_max_size_koeff, index_file )
             ) ) {
            return result;
        }
        // read id3 tags
        assert( id3_start < id3_end );
        assert( mel_start < mel_end );
        std::string artist, album, title, year;
        uint64_t record_size = id3_end - id3_start;
        if( ! id3_file.seekg( id3_start ).good() ) {
            std::cout << "ERROR: in id3 file\n";
            break;
        }
        std::getline( id3_file, artist );
        record_size -= id3_file.gcount();
        std::getline( id3_file, album );
        record_size -= id3_file.gcount();
        std::getline( id3_file, title );
        record_size -= id3_file.gcount();
        std::getline( id3_file, year );
        if( ! mel_file.seekg( mel_start ).good() ) {
            std::cout << "ERROR: in mel file\n";
            break;
        }
        std::vector< Raspoznavayka::interval_t > intervals( mel_end - mel_start );
        for( uint64_t i = 0; i < mel_end - mel_start; ++i ) {
            char interval;
            if( mel_file.get( interval ).fail() ) {
                std::cout << "ERROR: in mel file\n";
                break;
            }
            intervals[i] = static_cast< Raspoznavayka::interval_t >( interval );
        }
        CIDTag idtag( artist, album, title, std::atoi( year.c_str() ) );
        CInDBMelody new_melody( intervals, idtag );
        result.push_back( new_melody );
    } // end of found melodies' data read cycle

    id3_file.close();
    mel_file.close();
    index_file.close();
    return result;
}

std::vector< CHashMatch > CDataBase::searchByHash_offs( CHash hash ) const {
    std::vector< CHashMatch > result;
    std::ifstream hash_file;
    std::vector< std::pair< uint64_t, int64_t > > matches; // vector of pairs ( mel_id, offset )

    // hash offset cycle
    for( int64_t fixed_hash_offset = 0; 
            fixed_hash_offset < static_cast< int64_t >( hash.getLength() ) - static_cast< int64_t >( CFixedHash::length ); 
            ++fixed_hash_offset ) {

        CFixedHash fixed_hash( hash, fixed_hash_offset );
        std::string hash_filename = makeFilenameOfHash( fixed_hash );
        hash_file.open( makeFilenameOfHash( fixed_hash ),
                        std::fstream::in | std::fstream::binary );
        if( ! hash_file.is_open() ) {
            std::cout << "ERROR: Couldn't open hash file for reading: " << hash_filename << '\n';
            return result;
        }

        // fixed hash file read cycle
        while( hash_file.is_open() && hash_file.good() && hash_file.peek() != EOF ) {
            // read melody id
            uint64_t mel_id = 0;
            Raspoznavayka::mel_size_t mel_chm_offs = 0;
            if( ! ( read_number_from_file( mel_id, mel_number_size_koeff, hash_file ) // read melody id
                 && read_number_from_file( mel_chm_offs, mel_max_size_koeff, hash_file ) // read fixed hash match offset in melody
                 ) ) {
                return result;
            }
            
            int64_t total_offset = static_cast<int64_t>( mel_chm_offs ) - static_cast<int64_t>( fixed_hash_offset );
            // check distinct
            bool found = false;
            for( auto i = matches.begin(); i != matches.end(); ++i ) {
                if( i->first == mel_id && i->second == total_offset ) {
                    found = true;
                    break;
                }
            }
            if( !found ) {
                // push to matches
                matches.push_back( std::pair< uint64_t, int64_t >( mel_id, total_offset ) );
            }
        } // end of fixed hash file read cycle

        hash_file.close();
    } // end of hash offset cycle

    // read found melodies' data
    std::ifstream index_file;
    std::ifstream id3_file;
    std::ifstream mel_file;
    index_file.open( index_filename, std::fstream::in | std::fstream::binary );
    id3_file.open( id3_filename, std::fstream::in );
    mel_file.open( mel_filename, std::fstream::in | std::fstream::binary );
    if( ! ( index_file.is_open() && id3_file.is_open() && mel_file.is_open() ) ) {
        std::cout << "ERROR: Couldn't open some DB file for writing in " << directory << '\n';
        return result;
    }

    for( auto match = matches.begin(); match != matches.end(); ++match ) {
        int64_t mel_id = match->first, total_offset = match->second;
        // get index entry on this song
        index_file.seekg( mel_id * ( mel_number_size_koeff + mel_file_max_size_koeff ) );
        // get id3 and and melody addresses
        uint64_t id3_start = 0, id3_end = 0, mel_start = 0, mel_end = 0;
        if( ! ( read_number_from_file( id3_start, id3_file_max_size_koeff, index_file )
             && read_number_from_file( mel_start, mel_file_max_size_koeff, index_file )
             && read_number_from_file( id3_end, id3_file_max_size_koeff, index_file )
             && read_number_from_file( mel_end, mel_file_max_size_koeff, index_file )
             ) ) {
            return result;
        }
        // read id3 tags
        assert( id3_start < id3_end );
        assert( mel_start < mel_end );
        std::string artist, album, name, year;
        uint64_t record_size = id3_end - id3_start;
        if( ! id3_file.seekg( id3_start ).good() ) {
            std::cout << "ERROR: in id3 file\n";
            break;
        }
        std::getline( id3_file, artist );
        record_size -= id3_file.gcount();
        std::getline( id3_file, album );
        record_size -= id3_file.gcount();
        std::getline( id3_file, name );
        record_size -= id3_file.gcount();
        std::getline( id3_file, year );
        if( ! mel_file.seekg( mel_start ).good() ) {
            std::cout << "ERROR: in mel file\n";
            break;
        }
        std::vector< Raspoznavayka::interval_t > intervals( mel_end - mel_start );
        for( uint64_t i = 0; i < mel_end - mel_start; ++i ) {
            char interval;
            if( mel_file.get( interval ).fail() ) {
                std::cout << "ERROR: in mel file\n";
                break;
            }
            intervals[i] = static_cast< Raspoznavayka::interval_t >( interval );
        }
        CIDTag idtag( artist, album, name, std::atoi( year.c_str() ) );
        CInDBMelody new_melody( intervals, idtag );
        CHashMatch new_chm( &new_melody, total_offset );
        result.push_back( new_chm );
    } // end of found melodies' data read cycle

    id3_file.close();
    mel_file.close();
    index_file.close();
    return result;
}

std::vector< CInDBMelody > CDataBase::getEverything() const {
    std::vector< CInDBMelody > result;
    std::ifstream index_file;
    std::ifstream id3_file;
    std::ifstream mel_file;
    index_file.open( index_filename, std::fstream::in | std::fstream::binary );
    id3_file.open( id3_filename, std::fstream::in );
    mel_file.open( mel_filename, std::fstream::in | std::fstream::binary );
    if( ! ( index_file.is_open() && id3_file.is_open() && mel_file.is_open() ) ) {
        std::cout << "ERROR: Couldn't open some DB file for writing in " << directory << '\n';
        return result;
    }

    uint64_t id3_start = 0, id3_end = 0, mel_start = 0, mel_end = 0;
    // get id3 and and melody addresses
    if( ! ( read_number_from_file( id3_start, id3_file_max_size_koeff, index_file )
         && read_number_from_file( mel_start, mel_file_max_size_koeff, index_file )
         ) ) {
        return result;
    }
    while( index_file.good() && index_file.peek() != EOF ) {
        // get id3 and and melody addresses
        if( ! ( read_number_from_file( id3_end, id3_file_max_size_koeff, index_file )
             && read_number_from_file( mel_end, mel_file_max_size_koeff, index_file )
             ) ) {
            return result;
        }
        // read id3 tags
        assert( id3_start < id3_end );
        assert( mel_start < mel_end );
        std::string artist, album, name, year;
        uint64_t record_size = id3_end - id3_start;
        if( ! id3_file.seekg( id3_start ).good() ) {
            std::cout << "ERROR: in id3 file\n";
            break;
        }
        std::getline( id3_file, artist );
        record_size -= id3_file.gcount();
        std::getline( id3_file, album );
        record_size -= id3_file.gcount();
        std::getline( id3_file, name );
        record_size -= id3_file.gcount();
        std::getline( id3_file, year );
        if( ! mel_file.seekg( mel_start ).good() ) {
            std::cout << "ERROR: in mel file\n";
            break;
        }
        std::vector< Raspoznavayka::interval_t > intervals( mel_end - mel_start );
        for( uint64_t i = 0; i < mel_end - mel_start; ++i ) {
            char interval;
            if( mel_file.get( interval ).fail() ) {
                std::cout << "ERROR: in mel file\n";
                break;
            }
            intervals[i] = static_cast< Raspoznavayka::interval_t >( interval );
        }
        CIDTag idtag( artist, album, name, std::atoi( year.c_str() ) );
        CInDBMelody new_melody( intervals, idtag );
        result.push_back( new_melody );
        id3_start = id3_end;
        mel_start = mel_end;
    } // end of found melodies' data read cycle

    id3_file.close();
    mel_file.close();
    index_file.close();
    return result;
}

std::string CDataBase::makeFilenameOfHash( const CFixedHash &fixed_hash ) const {
    char filename_chars[] = "0123456789ABCDEF";
    unsigned int filename_length =  ( CFixedHash::length + 3 ) / 4;
    char *res = new char[ filename_length + 1 ];
    res[ filename_length ] = 0;
    int pow = 1;
    for( unsigned int a = 0; a < CFixedHash::length; ++a ) {
        if( a % 4 == 0 ) {
            pow = 1;
            res[ filename_length - a / 4 - 1 ] = 0;
        } else {
            pow *= 2;
        }
        if( fixed_hash.getHash()[CFixedHash::length - a - 1] == Raspoznavayka::arrow_up ) {
            res[ filename_length - a / 4 - 1 ] += pow;
        }
    }
    for( unsigned int a = 0; a < filename_length; ++a ) {
        res[a] = filename_chars[ static_cast< unsigned char >( res[a] ) ];
    }
    std::string ress( res );
    delete res;
    return hash_file_subdir + ress + hash_file_extension;
}

bool CDataBase::check_create_directory( const char* dir ) {
    struct stat sb;
    if( stat( dir, &sb ) != 0 ) {
        std::cout << "Directory \"" << dir << "\" does not exist. Trying to create one...\n";
        mode_t directory_mode =   S_IRUSR | S_IWUSR | S_IXUSR
                                | S_IRGRP | S_IWGRP | S_IXGRP
                                | S_IROTH;
        if( mkdir( dir, directory_mode ) == 0 ) {
            std::cout << "Directory \"" << dir << "\" created.\n";
            return true;
        } else {
            std::cout << "ERROR: Couldn't create directory \"" << dir << "\"!\nAborting. \n";
            assert( false );
            return false;
        }
    }
    else if ( (sb.st_mode & S_IFMT) != S_IFDIR ) {
        std::cout << "ERROR: \"" << dir << "\" exists, but is not a directory.\nAborting. \n";
        assert( false );
        return false;
    }
    return true;
}

template< typename num_type >
    bool CDataBase::read_number_from_file( num_type &number, unsigned int bytes, std::ifstream &file ) const {
        number = 0;
        for( unsigned int i = 0; i < bytes; ++i ) {
            char b = 0;
            if( ! file.read( &b, 1 ).good() ) {
                std::cout << "ERROR: reading number from some DB file\n";
                return false;
            }
            number = ( number << 8 ) + (unsigned char) b;
        }
        return true;
    }
