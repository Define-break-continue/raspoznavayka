class CIDTag {
public:
    std::string artist;
    std::string album;
    std::string title;
    std::int16_t year;

    CIDTag( std::string artist = "",
            std::string album = "",
            std::string title = "",
            std::int16_t year = 0 );

    void interactive_fill();
};
