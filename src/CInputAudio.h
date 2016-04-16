class CInputAudio {
    public:
    CInputAudio( std::string /*fileDest = "test.wav"*/ );
    std::vector< Aquila::SampleType > getSignal();
    void ReadAudioHelper( std::string );
    protected:
    std::vector< Aquila::SampleType > signal;
    void Resample( /**/ );
};
