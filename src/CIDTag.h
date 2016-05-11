class CIDTag {
public:
    std::string title;
    std::string artist;
    std::string album;
    std::int16_t year;

    CIDTag( std::string title = "",
            std::string artist = "",
            std::string album = "",
            std::int16_t year = 0 );

    void interactive_fill();
};
