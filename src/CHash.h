typedef std::int8_t _arrow_t;

#define _arrow_up 1
#define _arrow_equal 0
#define _arrow_down -1

class CHash {
public:
    CHash();
    template< typename CGeneralMelody >
        CHash( const CGeneralMelody& ); // CHash constructor for all Melody classes
    CHash( std::vector< _interval_t > );
/* TODO DELETE THIS:
 *    CHash( const CMelody& );
 *    CHash( const CInDBMelody& ); // ?? хочется вызывать CHash( const CMelody& ) для CInDBMelody, CRecordedMelody
 *                                // и прочих потомков CMelody не задумываясь о типах. Надо спросить как...
 *                               // а пока no known conversion for argument 1 from ‘CInDBMelody’ to ‘const CMelody&’
 */
    CHash getHash();
    _mel_size_t getLength();
protected:
    void setHash( std::vector< _interval_t > );
    std::vector< _arrow_t > arrows;
};

