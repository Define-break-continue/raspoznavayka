namespace Raspoznavayka {
    namespace Math {
    // these functions return Levenshtein distance for CRecordedMelody and:
        //whole CInDBMelody
        std::uint16_t getLevenshtein( const CRecordedMelody&, const CInDBMelody& );
        // CInDBMelody from offset to the end of melody
        std::uint16_t getLevenshtein( const CRecordedMelody&, const CInDBMelody&, std::int64_t offset );
        // CInDBMelody from begin (offset) to offset + end
        std::uint16_t getLevenshtein( const CRecordedMelody&, const CInDBMelody&, std::int64_t begin, std::int64_t end );
        // CHashMatch from offset to the end of melody
        std::uint16_t getLevenshtein( const CRecordedMelody&, const CHashMatch& );
        // CHashMatch from offset to offset + end
        std::uint16_t getLevenshtein( const CRecordedMelody&, const CHashMatch&, std::int64_t end );
        // CInDBMelody from offset to offset + CRecordedMelody length
        std::uint16_t getLevenshteinFixed( const CRecordedMelody&, const CInDBMelody&, std::int64_t offset );
        // CHashMatch from offset to offset + CRecordedMelody length
        std::uint16_t getLevenshteinFixed( const CRecordedMelody&, const CHashMatch& );

        // counts Levenshtein distance between two interval_t vectors
        std::uint16_t levenshtein( const std::vector< Raspoznavayka::interval_t >&, const std::vector< Raspoznavayka::interval_t >& ); 
    }
}
