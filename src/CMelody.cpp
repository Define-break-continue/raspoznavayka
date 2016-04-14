#include "CMelody.h"

namespace Raspoznavayka {
    typedef vector< vector < double > > Spectrogram;
}

CMelody::CMelody( std::vector< Aquila::SampleType >& waveform ) {
    setIntervals( waveform );
}

std::vector< Raspoznavayka::interval_t >& CMelody::getIntervals() {
    return intervals;
}

Raspoznavayka::mel_size_t CMelody::getLength() {
    return intervals.size();
}

// helper functions

// filter A coefficient based on frequency. For the proof-of-concept, a linear approximation used
auto dL( Aquila::FrequencyType& f ) {
    double x1, x2, y1, y2;
    x1 = x2 = y1 = y2 = 0;
    Aquila::FrequencyType frequencies[] = {
            0,    10,  12.5,    16,    20,    25,  31.5,    40,    50,    63,    80,
                 100,   125,   160,   200,   250,   315,   400,   500,   630,   800,
                1000,  1250,  1600,  2000,  2500,  3150,  4000,  5000,  6300,  8000,
               10000, 12500, 16000, 20000
    };
    double levels[] = {
         -300, -70.4, -63.4, -56.7, -50.5, -44.7, -39.4, -34.6, -30.2, -26.2, -22.5,
               -19.1, -16.1, -13.4, -10.9,  -8.6,  -6.6,  -4.8,  -3.2,  -1.9,  -0.8,
	           0,   0.6,   1.0,   1.2,   1.3,   1.2,   1.0,   0.5,  -0.1,  -1.1,
	        -2.5,  -4.3,  -6.6,  -9.3
    };

    int i = 0;
    for ( auto frequency : frequencies ) {
        if ( i > 0 ) {
            if ( f > frequencies[ i - 1 ] && f <= frequencies[ i ] ) {
                x1 = frequencies[ i - 1 ];
		y1 = levels[ i - 1 ];
		x2 = frequencies[ i ];
		y2 = levels[ i ];
	    }
	}
    }

    auto k = ( y2 - y1 ) / ( x2 - x1 );
    auto b = y1 - k * x1;
    auto dl = k * f + b;
    return dl;
}

Aquila::FrequencyType getFrequencyFromIteratorNumber( std::size_t i, std::size_t n ) {
    return SAMPLE_RATE / n * i;
}

// real spectrogram in dB/1, filter A
Raspoznavayka::Spectrogram getSpectrogram( const std::vector< Aquila::SampleType >& waveform ) {
    Aquila::SignalSource signal( waveform, SAMPLE_RATE );
    Aquila::FramesCollection frames( signal, SAMPLES_PER_FRAME, SAMPLES_PER_OVERLAP );
    Aquila::Spectrogram complexSpectrogram( frames );
    Raspoznavayka::Spectrogram realSpectrogram( complexSpectrogram.getFrameCount(), vector< double >( complexSpectrogram.getSpectrumSize(), 0 ) );
    for( std::size_t iF = 0; iF < complexSpectrogram.getSpectrumSize(); ++iF ) {
        for( std::size_t it = 0; it < complexSpectrogram.getFrameCount(); ++it ) {
            realSpectrogram[ it ][ iF ] = dB( complexSpectrogram.getPoint( it, iF ) )
	        + dL( getFrequencyFromIteratorNumber( iF, complexSpectrogram.getSpectrumSize() ) );
	}
    }
    return realSpectrogram;
}

void CMelody:setIntervals( std::vector< Aquila::SampleType >& waveform ) {
    // TODO main code of physics part will be here
}
