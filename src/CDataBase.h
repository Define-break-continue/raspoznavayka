class CDataBase {
public:
    static const CDataBase& getInstance();
    std::vector< CHashMatch > searchByHash_offs( CHash hash ) const;
    std::vector< CInDBMelody > searchByHash( CHash hash ) const;
    std::vector< CInDBMelody > getEverything() const;
    bool addMelody( CInDBMelody melody ) const;
private:
    CDataBase();
    CDataBase( const CDataBase &a ) = delete;
    CDataBase& operator=( const CDataBase &a ) = delete;
    std::string makeFilenameOfHash( const CFixedHash &fixed_hash ) const;
    bool check_create_directory( const char* );
    template< typename num_type >
        bool read_number_from_file( num_type &number, unsigned int bytes, std::ifstream &file ) const;
    std::string directory;
    std::string index_filename;
    std::string id3_filename;
    std::string mel_filename;
    std::string hash_file_subdir;
    std::string hash_file_extension;
    int id3_file_max_size_koeff;
    int mel_file_max_size_koeff;
    int mel_max_size_koeff;
    int mel_number_size_koeff;
};

