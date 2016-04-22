#include "raspoznavayka.h"

CMelody::CMelody( std::vector< Aquila::SampleType >& waveform ) : intervals( 0 ) {
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
auto dL( Aquila::FrequencyType f ) {
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

inline Aquila::FrequencyType getFrequencyFromIteratorNumber( std::size_t i, std::size_t n ) {
    return SAMPLE_RATE / n * i;
}

// real spectrogram in dB/1, filter A
// Raspoznavayka::Spectrogram getSpectrogram( const std::vector< Aquila::SampleType >& waveform ) {
//     Aquila::SignalSource signal( waveform, SAMPLE_RATE );
//     Aquila::FramesCollection frames( signal, SAMPLES_PER_FRAME, SAMPLES_PER_OVERLAP );
//     Aquila::Spectrogram complexSpectrogram( frames );
//     Raspoznavayka::Spectrogram realSpectrogram( complexSpectrogram.getFrameCount(), std::vector< double >( complexSpectrogram.getSpectrumSize(), 0 ) );
//     for( std::size_t iF = 0; iF < complexSpectrogram.getSpectrumSize(); ++iF ) {
//         for( std::size_t it = 0; it < complexSpectrogram.getFrameCount(); ++it ) {
//             realSpectrogram[ it ][ iF ] = Aquila::dB( complexSpectrogram.getPoint( it, iF ) )
// 	        + dL( getFrequencyFromIteratorNumber( iF, complexSpectrogram.getSpectrumSize() ) );
// 	}
//     }
//     return realSpectrogram;
// }

inline Raspoznavayka::dB_t dBSum( Raspoznavayka::dB_t a, Raspoznavayka::dB_t b ) {
    Raspoznavayka::dB_t max = std::max( a, b );
    Raspoznavayka::dB_t min = std::min( a, b );
    switch( std::round( max - min ) ) {
        case 0: return max + 3;
	case 1: return max + 2.5;
	case 2:
	case 3: return max + 2;
	case 4: return max + 1.5;
	case 5:
	case 6:
	case 7: return max + 1;
	case 8:
	case 9: return max + 0.5;
    }
    return max;
}

inline void notePowerReset( vector< Raspoznavayka::dB_t >& notePower ) {
    for( auto i = 0; i < notePower.size(); ++i )
        notePower[ i ] = std::numeric_limits< Raspoznavayka::dB_t >::min();
}

inline Raspoznavayka::note_t LoudestNote( vector< dB_t >& notePower ) {
    Raspoznavayka::dB_t maxPower = std::numeric_limits< Raspoznavayka::dB_t >::min();
    Raspoznavayka::note_t result = LOWEST_NOTE;
    for( Raspoznavayka::note_t note = LOWEST_NOTE; note <= HIGHEST_NOTE; ++note ) {
         if( notePower[ note ] >= maxPower ) {
	     maxPower = notePower[ note ];
	     result = note;
	 }
    }
}

void CMelody::setIntervals( std::vector< Aquila::SampleType >& waveform ) {
    Aquila::SignalSource signal( waveform, SAMPLE_RATE );
    Aquila::FramesCollection frames( signal, SAMPLES_PER_FRAME, SAMPLES_PER_OVERLAP );
    auto fft = Aquila::FftFactory::getFft( SAMPLES_PER_FRAME ); // create an fft object
    vector< Raspoznavayka::dB_t > notePower( Raspoznavayka::note_t::HIGHEST_NOTE - Raspoznavayka::note_t::LOWEST_NOTE + 1, std::numeric_limits< Raspoznavayka::dB_t >::min() ); // for note power count

    Aquila::SpectrumType complexSpectrum( SAMPLES_PER_FRAME );
    for( auto frame : frames ) { // for each frame
        complexSpectrum = fft->fft( frame.toArray() ); // count complex spectrum
	Raspoznavayka::note_t note = LOWEST_NOTE;
        for( auto c = complexSpectrum.begin(), std::size_t i = 0; c != complexSpectrum.end(); ++c, ++i ) {
	    auto f = getFrequencyFromIteratorNumber( i );
            Raspoznavayka::dB_t L = Aquila::dB( *c ) + dL( f ); // real spectrum, filter A
	    if( note > HIGHEST_NOTE + NEEDED_HALFTONES_TO_THE_LAST_OBERTONE ) // no need to count higher spectrum
	        break;
	    if( f >= note_freq[ note + 1 ] ) // increment the note
	        note++;
	    else if( f >= note_freq[ note ] ) { // hardcode: we need to add powers to the current note and to 2 lower octaves. TODO: add a macros for variable number of octaves
	        if( note >= LOWEST_NOTE && note <= HIGHEST_NOTE )
		    notePower[ note ] = dBSum( notePower[ note ], L );
		if( note >= LOWEST_NOTE + HALFTONES_IN_AN_OCTAVE && note <= HIGHEST_NOTE + HALFTONES_IN_AN_OCTAVE )
		    notePower[ note - HALFTONES_IN_AN_OCTAVE ] = dBSum( notePower[ note - HALFTONES_IN_AN_OCTAVE ], L );
		if( note >= LOWEST_NOTE + 2 * HALFTONES_IN_AN_OCTAVE && note <= HIGHEST_NOTE + 2 * HALFTONES_IN_AN_OCTAVE )
		    notePower[ note - 2 * HALFTONES_IN_AN_OCTAVE ] = dBSum( notePower[ note - 2 * HALFTONES_IN_AN_OCTAVE ], L );
            }
	// now we have all notes' powers
	Raspoznavayka::note_t loudestNote = LoudestNote( notePower );
...
	notePowerReset( notePower );
	}
    }
}
