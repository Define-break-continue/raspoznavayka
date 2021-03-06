#include "raspoznavayka.h"

CMelody::CMelody( std::vector< Aquila::SampleType >& waveform ) : intervals( 0 ) {
    setIntervals( waveform );
}

CMelody::CMelody( const std::vector< Raspoznavayka::interval_t >& intervals ) : intervals( intervals ) {}

const std::vector< Raspoznavayka::interval_t >& CMelody::getIntervals() const {
    return intervals;
}

Raspoznavayka::mel_size_t CMelody::getLength() const {
    return intervals.size();
}

// helper functions
inline Aquila::FrequencyType getFrequencyFromIteratorNumber( std::size_t i ) {
    return ( (double) SAMPLE_RATE ) * i / SAMPLES_PER_FRAME;
}

// TODO: rewrite the function with the array of n=SAMPLE_RATE dl-s
// filter A coefficient based on frequency. For the proof-of-concept, a linear approximation used
inline Raspoznavayka::dB_t dL( Aquila::FrequencyType f ) {
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
    for ( ; i < frequencies.size() && f >= frequencies[ i ]; ++i );
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

std::vector< Raspoznavayka::note_t > getNotesVectorFromFrequency( Aquila::FrequencyType f ) {
    // if frequency is wrong
    if( f <= 0 ) {
        Raspoznavayka::frequencyError();
    }
    if( f < Raspoznavayka::note_freq[ LOWEST_NOTE ] ) {
        return std::vector< Raspoznavayka::note_t >( static_cast< Raspoznavayka::note_t >( 0 ) );
    }
    if( [ f ]() { Aquila::FrequencyType fr = f;
                  for( std::size_t i = 1; i < LEVEL_ADDITION_N_OCTAVES; ++i ) fr /= 2;
                  return fr;
        }() > Raspoznavayka::note_freq[ HIGHEST_NOTE ] )
        return  std::vector< Raspoznavayka::note_t >( static_cast< Raspoznavayka::note_t >( 0 ) );
    //iterator range
    int octaveRestriction = LEVEL_ADDITION_N_OCTAVES;
    while( f > Raspoznavayka::note_freq[ HIGHEST_NOTE ] ) {
        f /= 2;
        --octaveRestriction;
    }
    // find the note
    Raspoznavayka::note_t note = LOWEST_NOTE;
    while( f >= Raspoznavayka::note_freq[ note ] ) {
        ++note;
    }
    // vector of notes or zeroes
    std::vector< Raspoznavayka::note_t > result( octaveRestriction, static_cast< Raspoznavayka::note_t >( 0 ) );
    for( int octave = 0; octave < octaveRestriction; ++octave ) {
        Raspoznavayka::note_t currentNote = static_cast< Raspoznavayka::note_t >( note - octave * HALFTONES_IN_AN_OCTAVE );
        if( currentNote <= HIGHEST_NOTE ) {
           result[ octave ] = currentNote;
        }
    }
    return result;
}

Raspoznavayka::note_t getNoteFromFrequency( Aquila::FrequencyType f ) {
    if( f <= 0 ) {
        Raspoznavayka::frequencyError();
    }
    if( f < Raspoznavayka::note_freq[ LOWEST_NOTE ] || f > Raspoznavayka::note_freq[ HIGHEST_NOTE + ( LEVEL_ADDITION_N_OCTAVES - 1 ) * HALFTONES_IN_AN_OCTAVE ] ) {
        return static_cast< Raspoznavayka::note_t >( 0 );
    }
    // find the note
    Raspoznavayka::note_t note = LOWEST_NOTE;
    while( f >= Raspoznavayka::note_freq[ note ] )
        ++note;
    return note;
}

void CMelody::setIntervals( std::vector< Aquila::SampleType >& waveform ) {
    Aquila::SignalSource signal( waveform, SAMPLE_RATE );
    Aquila::FramesCollection frames( signal, SAMPLES_PER_FRAME, SAMPLES_PER_OVERLAP );
    auto fft = Aquila::FftFactory::getFft( SAMPLES_PER_FRAME ); // create an fft object
    Aquila::SpectrumType complexSpectrum( SAMPLES_PER_FRAME, 0 );
//    std::vector< Raspoznavayka::dB_t > notePower( HIGHEST_NOTE + 1, Raspoznavayka::dB_t().min() ); // for note power count; note_index == note
    std::vector< Raspoznavayka::dB_t > notePower( HIGHEST_NOTE + ( LEVEL_ADDITION_N_OCTAVES - 1 ) * HALFTONES_IN_AN_OCTAVE + 1, Raspoznavayka::dB_t().min() ); // for note power count; note_index == note
    std::vector< Raspoznavayka::note_t > melody;
    Raspoznavayka::dB_t currentNoteLevel = Raspoznavayka::dB_t().min();

    for( auto frame : frames ) { // for each frame
        complexSpectrum = fft->fft( frame.toArray() ); // count complex spectrum
        std::size_t i = 1;
        for( auto c = complexSpectrum.begin() + 1; c < complexSpectrum.end(); ++c, ++i ) {
            auto f = getFrequencyFromIteratorNumber( i );
            Raspoznavayka::dB_t L = Aquila::dB( *c ) << dL( f ); // real spectrum, filter A; << is arithmetical addition for dB_t
            if( f >= Raspoznavayka::note_freq[ HIGHEST_NOTE + 1 + ( LEVEL_ADDITION_N_OCTAVES - 1 ) * HALFTONES_IN_AN_OCTAVE ] ) {
                break;
            }
//            auto notes = getNotesVectorFromFrequency( f );
            auto note = getNoteFromFrequency( f );
//            for( auto note : notes ) {
//                if( note != 0 )
//                    if( notePower[ note ] > Raspoznavayka::dB_t().min() )
//                        notePower[ note ] %= L; // % is rms
//                    else
//                        notePower[ note ] = L;
//            }
            if( note )
                if( notePower[ note ] > Raspoznavayka::dB_t().min() )
                    notePower[ note ] %= L; // % is rms
                else
                    notePower[ note ] = L;
        }
        for( auto note = LOWEST_NOTE; note <= HIGHEST_NOTE; ++note ) {
            for( std::size_t i = 1; i < LEVEL_ADDITION_N_OCTAVES; ++i ) {
                auto additionNote = static_cast< Raspoznavayka::note_t >( static_cast< std::uint8_t >( note ) + i * HALFTONES_IN_AN_OCTAVE );
                if( additionNote < Raspoznavayka::note_freq.size() )
                    notePower[ note ] += notePower[ additionNote ];
            }
        }
        // now we have all notes' powers
        auto loudestNotePoiner = std::max_element( notePower.begin(), notePower.end() );
        Raspoznavayka::note_t loudestNote = static_cast< Raspoznavayka::note_t >( std::distance( notePower.begin(), loudestNotePoiner ) );
        Raspoznavayka::dB_t loudestNoteLevel = notePower[ loudestNote ];
        if( melody.empty() || ( loudestNoteLevel >> currentNoteLevel ) <= MAXIMUM_DIFFERENCE_OF_LEVEL_OF_TWO_NEAREST_NOTES && melody.at( melody.size() - 1 ) != loudestNote ) {
            melody.push_back( loudestNote );
            currentNoteLevel = loudestNoteLevel;
        }
        std::fill( notePower.begin(), notePower.end(), Raspoznavayka::dB_t().min() ); // reset notePower vector values
        loudestNoteLevel = Raspoznavayka::dB_t().min();
    }

    // now we have the melody recorded in notes
    // counting interval vector
    intervals = std::vector< Raspoznavayka::interval_t >( melody.size() - 1 ); // N notes --> N - 1 intervals
    for( std::size_t i = 0; i < intervals.size(); ++i ) {
        intervals[ i ] = melody[ i + 1 ] - melody[ i ];
    }
}

void CMelody::printIntervals() {
    std::vector< Raspoznavayka::interval_t > intervals = this->getIntervals();
    for( std::vector< Raspoznavayka::interval_t >::iterator i = intervals.begin(); i < intervals.end(); ++i ) {
        if( ( i - intervals.begin() ) % 8 == 0 )
            std::cout << std::endl;
        std::cout << *i << '\t';
    }
    std::cout << std::endl;
}

