class CInDBMelody : public CMelody {
public:
    CInDBMelody( std::vector< Raspoznavayka::interval_t > intervals );
    CInDBMelody( CMelody& melody );
    CInDBMelody( std::vector< Raspoznavayka::interval_t > intervals, CIDTag& idTag );
    CInDBMelody( CMelody& melody, CIDTag& idTag );
    CIDTag getIDTag();
protected:
    CIDTag idTag;
};
