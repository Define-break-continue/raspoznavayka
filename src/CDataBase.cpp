#include "raspoznavayka.h"

const CDataBase CDataBase::getInstance() {
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
                            // this koeff should be less or (better) equal to _mel_size_t
    assert( sizeof( mel_max_size_koeff ) <= sizeof( _mel_size_t ) ); 
    mel_number_size_koeff = 4; // number of bytes to store a melody's index
    hash_file_extension = std::string( ".hash" );
    /*
     * ... till here
     * a database is shipped with its .config and both
     * are platform-independent
     */
}

bool CDataBase::addMelody( CInDBMelody melody ) {
    std::ofstream id3_file;
    std::ofstream mel_file;
    std::ofstream index_file;
    index_file.open( index_filename, std::fstream::out | std::fstream::app );

    // check if index file is empty
    if( index_file.tellp() == 0 ) {
        // if index file is empty, write initial zeros as the first entry address
        for( int i = 0; i < id3_file_max_size_koeff + mel_file_max_size_koeff; ++i ) {
            index_file.write( "0", 1 );
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
        return flase;
    }

    // write melody
    std::vector< interval_t > mel_intervals = melody.getIntervals();
    _mel_size_t mel_size = mel_intervals.size();
    char *mel_char_intervals = new char[mel_size];
    for( std::vector< interval_t >::size_type i = 0; i < mel_size; ++i ) {
        mel_char_intervals[i] = mel_intervals[i];
    }
    mel_file.write( mel_char_intervals, mel_size );
    delete mel_char_intervals;

    // write id3 tags
    std::string artist, album, name, year;
    std::cout << "Tell me of this new song!\nWho's the artist?\n";
    std::cin >> artist;
    std::cout << "Awh, I guessed it! And the album is...\n";
    std::cin >> album;
    std::cout << "Yeah, it's one of " << artist << "'s best! What's that song's name?\n";
    std::cin >> name;
    std::cout << "Names are unneeded. What year " << artist << " recorded it?\n";
    std::cin >> year;
    std::cout << "Anyway, I prefer debian_netinst.iso at 44100 Hz to this stuff!\n\n";
    id3_file << artist << album << name << year << '\n';

    // get positions at id3 and melody files, store
    // them in index file
    std::streampos pos = mel_file.tellp();
    for( int i = 0; i < id3_file_max_size_koeff; ++i ) {
        index_file.write( ((char*)&pos) + sizeof( pos ) - i - 1, 1 );
    }
    pos = id3_file.tellp();
    for( int i = 0; i < id3_file_max_size_koeff; ++i ) {
        index_file.write( ((char*)&pos) + sizeof( pos ) - i - 1, 1 );
    }
    // make pos = index of the song currently being added
    pos = index_file.tellp() / ( mel_file_max_size_koeff + id3_file_max_size_koeff );
    pos -= 1;
    id3_file.close();
    mel_file.close();
    index_file.close();

    // iterate through the song's FixedHashes
    CHash hash( melody );
    for( _mel_size_t offset = 0; offset < mel_size - CFixedHash::length; ++offset ) {
        CFixedHash fixed_hash( hash, offset );
        // open the appropriate hash file to write current fixed hash match to 
        std::ofstream hash_file;
        hash_file.open( makeFilenameOfHash( fixed_hash ),
                       std::fstream::out | std::fstream::app | std::fstream::binary );
        if( ! hash_file.is_open() ) {
            std::cout << "ERROR: Couldn't open DB hash file for writing: " << makeFilenameOfHash( fixed_hash ) << '\n';
            return false;
        }
        // write melody id
        for( int i = 0; i < mel_number_size_koeff; ++i ) {
            hash_file.write( ((char*)&pos) + sizeof( pos ) - i - 1, 1 );
        }
        // write fixed hash match offset
        for( int i = 0; i < mel_number_size_koeff; ++i ) {
            hash_file.write( ((char*)&pos) + sizeof( pos ) - i - 1, 1 );
        }
        hash_file.close();
    }
    return true;
}

std::vector<CHashMatch> CDataBase::searchByHash( CFixedHash fixed_hash ) {
    std::ifstream index_file;
    std::ifstream id3_file;
    std::ifstream mel_file;
    std::ifstream hash_file;
    index_file.open( index_filename, std::fstream::in );
    id3_file.open( id3_filename, std::fstream::in );
    mel_file.open( mel_filename, std::fstream::in );
    hash_file.open( makeFilenameOfHash( fixed_hash ), std::fstream::in );
}

std::string CDataBase::makeFilenameOfHash( const CFixedHash &fixed_hash ) {
    char filename_chars[] = "0123456789ABCDEF";
    int filename_length =  ( CFixedHash::length + 3 ) / 4;
    char *res = new char[filename_length];
    int pow = 1;
    for( int a = 0; a < CFixedHash::length; ++a ) {
        if( a % 4 == 0 ) {
            pow = 1;
            res[ filename_length - a - 1 ] = 0;
        } else {
            pow *= 2;
        }
        if( fixed_hash.arrows[CFixedHash::length - a - 1] == _arrow_up ) {
            res[ filename_length - a / 4 - 1 ] += pow;
        }
    }
    for( int a = 0; a < filename_length; ++a ) {
        res[a] = filename_chars[res[a]];
    }
    std::string ress( res );
    delete res;
    return hash_file_subdir + ress + hash_file_extension;
}

