class CDataBase {
public:
    static const CDataBase getInstance();
    std::vector<CHashMatch> searchByHash( CFixedHash fixed_hash );
    bool addMelody( CInDBMelody melody );
private:
    CDataBase();
    CDataBase( const CDataBase &a );
    CDataBase& operator=( const CDataBase &a );
    std::string makeFilenameOfHash( const CFixedHash &fixed_hash );
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

