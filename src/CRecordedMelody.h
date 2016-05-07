class CRecordedMelody : public CMelody {
    public:
    CRecordedMelody( std::vector< Aquila::SampleType >& waveform );
    CRecordedMelody( std::vector< Raspoznavayka::interval_t >& intervals );
    const CHash& getHash() const;

    protected:
    CHash hash;
};
