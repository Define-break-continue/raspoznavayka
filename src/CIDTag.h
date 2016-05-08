class CIDTag {
public:
    std::string title;
    std::string artist;
    std::string album;
    std::uint8_t year;

    CIDTag( std::string title = "",
            std::string artist = "",
            std::string album = "",
            std::uint8_t year = 0 );
};
