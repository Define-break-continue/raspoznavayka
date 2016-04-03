#ifndef __IDTAG_
#define __IDTAG_

#include "raspoznavayka.h"
#include <string>

struct CIDTag {
    std::string title;
    std::string artist;
    std::string album;
    std::uint8_t year;

    CIDTag(): title( 0 ),
              artist( 0 ),
	      album( 0 ),
	      year( 0 ) {}
    CIDTag( std::string title ) : title( title ),
                                  artist( 0 ),
                                  album( 0 ),
                                  year( 0 ) {}
    CIDTag( std::string title, std::string artist ) : CIDTag( title ), artist( artist ) {}
    CIDTag( std::string title, std::string artist, std::string album ) : CIDTag( title, artist ), album( album ) {}
    CIDTag( std::string title, std::string artist, std::string album, std::uint8_t year ) : CIDTag( title, artist, album ), year( year ) {}

};

#endif // __IDTAG_
