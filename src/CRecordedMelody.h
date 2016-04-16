class CRecordedMelody : public CMelody {
    public:
    CRecordedMelody( std::vector< Aquila::SampleType >& waveform ) : CMelody( waveform ), hash( 0 ) {}
    CRecordedMelody( std::vector< Raspoznavayka::interval_t >& intervals ) : CMelody( intervals ), hash( 0 ) {}
    CHash& getHash();

    protected:
    CHash hash;
    void setHash();
};
