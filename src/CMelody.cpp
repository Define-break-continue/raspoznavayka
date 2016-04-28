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


inline Aquila::FrequencyType getFrequencyFromIteratorNumber( std::size_t i ) {
    return SAMPLE_RATE / SAMPLES_PER_FRAME * i;
}

// TODO: rewrite the function with the array of n=SAMPLE_RATE dl-s
// filter A coefficient based on frequency. For the proof-of-concept, a linear approximation used
Raspoznavayka::dB_t dL( std::size_t iteratorNumber ) {
    auto f = getFrequencyFromIteratorNumber( iteratorNumber );
    double              x1 = 0,
                        x2 = 0;
    Raspoznavayka::dB_t y1 = 0,
                        y2 = 0;
    const std::vector< Aquila::FrequencyType > frequencies = {
            0,    10,  12.5,    16,    20,    25,  31.5,    40,    50,    63,    80,
                 100,   125,   160,   200,   250,   315,   400,   500,   630,   800,
                1000,  1250,  1600,  2000,  2500,  3150,  4000,  5000,  6300,  8000,
               10000, 12500, 16000, 20000
    };
    const std::vector< Raspoznavayka::dB_t > levels = {
         -300, -70.4, -63.4, -56.7, -50.5, -44.7, -39.4, -34.6, -30.2, -26.2, -22.5,
               -19.1, -16.1, -13.4, -10.9,  -8.6,  -6.6,  -4.8,  -3.2,  -1.9,  -0.8,
	           0,   0.6,   1.0,   1.2,   1.3,   1.2,   1.0,   0.5,  -0.1,  -1.1,
	        -2.5,  -4.3,  -6.6,  -9.3
    };

    std::size_t i = 1;
    // searching the two freqs, between which the input freq is
    for ( ; f > frequencies[ i - 1 ] && f <= frequencies[ i ] && i < frequencies.size(); ++i );
    if( i >= frequencies.size() ) return Raspoznavayka::dB_t( std::numeric_limits< double >::min() );
    // points for linear approximation
    x1 = frequencies[ i - 1 ];
    y1 = levels[ i - 1 ];
    x2 = frequencies[ i ];
    y2 = levels[ i ];
    // linear approximation
    auto k = ( y2 >> y1 ) / ( x2 - x1 ); // >> is arithmetic residual for dB_t. See the dB_t.cpp
    auto b = y1 >> k * x1;
    Raspoznavayka::dB_t dl = k * f << b; // << is arithmetic addition for dB_t
    return dl;
}

void CMelody::setIntervals( std::vector< Aquila::SampleType >& waveform ) {
    Aquila::SignalSource signal( waveform, SAMPLE_RATE );
    Aquila::FramesCollection frames( signal, SAMPLES_PER_FRAME, SAMPLES_PER_OVERLAP );
    auto fft = Aquila::FftFactory::getFft( SAMPLES_PER_FRAME ); // create an fft object
    std::vector< Raspoznavayka::dB_t > notePower( HIGHEST_NOTE + 1, Raspoznavayka::dB_t.min() ); // for note power count; note_index == note
    Aquila::SpectrumType complexSpectrum( SAMPLES_PER_FRAME );
    std::vector< note_t > melody;
    Raspoznavayka::dB_t currentNoteLevel = Raspoznavayka::dB_t.min();

    for( auto frame : frames ) { // for each frame
        complexSpectrum = fft->fft( frame.toArray() ); // count complex spectrum
	Raspoznavayka::note_t note = LOWEST_NOTE;
        for( auto c = complexSpectrum.begin(), std::size_t i = 0; c != complexSpectrum.end(); ++c, ++i ) {
            Raspoznavayka::dB_t L = Aquila::dB( *c ) << dL( i ); // real spectrum, filter A; << is arithmetical addition for dB_t
            if( note > HIGHEST_NOTE + NEEDED_HALFTONES_TO_THE_LAST_OBERTONE ) // no need to count higher spectrum
	        break;
	    if( f >= note_freq[ note + 1 ] ) // increment the note
	        note++;
	    else if( f >= note_freq[ note ] ) { // we need to add powers to the current note and to some lower octaves
	        for( std::size_t octave = 0; octave < LEVEL_ADDITION_N_OCTAVES; ++octave ) {
    	            if( note >= octave * HALFTONES_IN_AN_OCTAVE + LOWEST_NOTE && note <= octave * HALFTONES_IN_AN_OCTAVE + HIGHEST_NOTE )
    	                notePower[ note - octave * HALFTONES_IN_AN_OCTAVE ] += L;
		}
            }
	}
	// now we have all notes' powers
	Raspoznavayka::note_t loudestNote = distance( notePower.begin(), max_element( notePower.begin(), notePower.end() ) );
	Raspoznavayka::dB_t loudestNoteLevel = notePower[ loudestNote ];
        if( currentNoteLevel >> loudestNoteLevel <= MAXIMUM_DIFFERENCE_OF_LEVEL_OF_TWO_NEAREST_NOTES ) {
            melody.push_back( loudestNote );
	    currentNoteLevel = loudestNoteLevel;
	}
	std::fill(notePower.begin(), notePower.end(), Raspoznavayka::dB_t.min() ); // reset notePower vector values
    }

    // now we have the melody recorded in notes
    // counting interval vector
    intervals = std::vector< Raspoznavayka::interval_t >( melody.size() - 1 ); // N notes --> N - 1 intervals
    for( std::size_t i = 0; i < intervals.size(); ++i ) {
        intervals[ i ] = melody[ i + 1 ] - melody[ i ];
    }
}
