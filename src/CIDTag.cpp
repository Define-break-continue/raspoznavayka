#include "raspoznavayka.h"

CIDTag::CIDTag( std::string artist,
                std::string album,
                std::string title,
                std::int16_t year ) : artist( artist ),
                                      album( album ),
                                      title( title ),
                                      year( year ) {}

void CIDTag::interactive_fill() {
    std::cout << "Tell me of this new song!\nWho's the artist?\n";
    std::cin >> artist;
    std::cout << "Awh, I guessed it! And the album is...\n";
    std::cin >> album;
    std::cout << "Yeah, it's one of " << artist << "'s best! What's that song's name?\n";
    std::cin >> title;
    std::cout << "Names are unneeded. What year " << artist << " recorded it?\n";
    std::cin >> year;
    std::cout << "Anyway, I prefer debian_netinst.iso at 44100 Hz to this stuff!\n\n";
}

