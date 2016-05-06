#ifndef __IDTAG_
#define __IDTAG_

struct CIDTag {
    std::string title;
    std::string artist;
    std::string album;
    std::uint8_t year;

    CIDTag( std::string title = 0,
            std::string artist = 0,
	    std::string album = 0,
	    std::uint8_t year = 0 ) : title( title ),
	                              artist( artist ),
				      album( album ),
				      year( year ) {}
};

#endif // __IDTAG_
