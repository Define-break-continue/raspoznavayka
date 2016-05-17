namespace Raspoznavayka {
    enum interval_t : std::int8_t {
        m2_interval = 1,
        M2_interval,
        m3_interval,
        M3_interval,
        P4_interval,
        A4_interval = 6,
        d5_interval = 6,
        P5_interval = 7,
        m6_interval = 8,
        M6_interval,
        m7_interval,
        M7_interval,
        P8_interval,
        m9_interval,
        M9_interval,
        m10_interval,
        M10_interval,
        P11_interval,
        A11_interval = 18,
        d12_interval = 18,
        P12_interval = 19,
        m13_interval,
        M13_interval,
        m14_interval,
        M14_interval,
        P15_interval,
        m16_interval,
        M16_interval,
        m17_interval,
        M17_interval,
        P18_interval,
        A18_interval = 30, 
        d19_interval = 30,
        P19_interval = 31,
        m20_interval,
        M20_interval,
        m21_interval,
        M21_interval,
        P22_interval,
    
        pause_interval = 0,
        PAUSE_interval = 0,
        P_interval = 0,
        p_interval = 0,
    
        dP22_interval = -36,
        dM21_interval = -35,
        dm21_interval,
        dM20_interval,
        dm20_interval,
        dP19_interval,
        dd19_interval = -30,
        dA18_interval = -30,
        dP18_interval = -29,
        dM17_interval,
        dm17_interval,
        dM16_interval,
        dm16_interval,
        dP15_interval,
        dM14_interval,
        dm14_interval,
        dM13_interval,
        dm13_interval,
        dP12_interval,
        dd12_interval = -18, 
        dA11_interval = -18,
        dP11_interval = -17,
        dM10_interval,
        dm10_interval,
        dM9_interval,
        dm9_interval,
        dP8_interval,
        dM7_interval,
        dm7_interval,
        dM6_interval,
        dm6_interval,
        dP5_interval,
        dd5_interval = -6,
        dA4_interval = -6,
        dP4_interval = -5,
        dM3_interval,
        dm3_interval,
        dM2_interval,
        dm2_interval
    };

    enum note_t : std::uint8_t {
        C = 1,
            Db,  D,  Eb,  E,  F,  Gb,  G,  Ab,  A,  Bb,  B,
        c,  db,  d,  eb,  e,  f,  gb,  g,  ab,  a,  bb,  b,
        c1, d1b, d1, e1b, e1, f1, g1b, g1, a1b, a1, b1b, b1,
        c2, d2b, d2, e2b, e2, f2, g2b, g2, a2b, a2, b2b, b2,
        c3, d3b, d3, e3b, e3, f3, g3b, g3, a3b, a3, b3b, b3,
        c4, d4b, d4, e4b, e4, f4, g4b, g4, a4b, a4, b4b, b4,
        c5, d5b, d5, e5b, e5, f5, g5b, g5, a5b, a5, b5b, b5,
        c6, // c6 is used as the top freq of b5 interval; octaves 4 and 5 for obertones power count
        P = 0, p = 0, PAUSE = 0
    };

    note_t& operator++( note_t& n );
    note_t operator+( const note_t& a, const int& b );
    note_t operator+( const note_t& a, const std::size_t& b );

    interval_t& operator++( interval_t& n );
    interval_t operator+( const interval_t& a, const int& b );
    interval_t operator+( const interval_t& a, const std::size_t& b );
    interval_t operator-( const note_t& a, const note_t& b );
    const std::vector< Aquila::FrequencyType > note_freq = []() {
        auto note = C;
        std::vector< Aquila::FrequencyType > v( HIGHEST_NOTE + LEVEL_ADDITION_N_OCTAVES * HALFTONES_IN_AN_OCTAVE + 1 );
        for( auto frequency = v.begin() + 1; frequency < v.end(); ++frequency, ++note ) {
            *frequency = 65.406 * pow( 2, (double) ( note - 1 ) / 12.0 - 1.0 / 24.0 );
        }
        v[ 0 ] = 0;
        return v;
    }();
}
