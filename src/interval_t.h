namespace Raspoznavayka {
    enum interval_t : std::uint8_t {
        m2 = 1,
        M2,
        m3,
        M3,
        P4,
        A4 = 6,
        d5 = 6,
        P5 = 7,
        m6 = 8,
        M6,
        m7,
        M7,
        P8,
        m9,
        M9,
        m10,
        M10,
        P11,
        A11 = 18,
        d12 = 18,
        P12 = 19,
        m13,
        M13,
        m14,
        M14,
        P15,
        m16,
        M16,
        m17,
        M17,
        P18,
        A18 = 30, 
        d19 = 30,
        P19 = 31,
        m20,
        M20,
        m21,
        M21,
        P22,
    
        pause = 0,
        PAUSE = 0,
        P = 0,
        p = 0,
    
        dP22 = -36,
        dM21 = -35,
        dm21,
        dM20,
        dm20,
        dP19,
        dd19 = -30,
        dA18 = -30,
        dP18 = -29,
        dM17,
        dm17,
        dM16,
        dm16,
        dP15,
        dM14,
        dm14,
        dM13,
        dm13,
        dP12,
        dd12 = -18, 
        dA11 = -18,
        dP11 = -17,
        dM10,
        dm10,
        dM9,
        dm9,
        dP8,
        dM7,
        dm7,
        dM6,
        dm6,
        dP5,
        dd5 = -6,
        dA4 = -6,
        dP4 = -5,
        dM3,
        dm3,
        dM2,
        dm2
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

    std::map< Aquila::FrequencyType, note_t > note_freq; // each value is the lowest frequency of the note bandwidth
    for( note_t note = C; note < c6; ++note ) {
        note_freq.insert( std::pair< note_t, Aquila::FrequencyType >( note, 65.406 * cmath::pow( 2, ( note - 1 ) / 12 - 1 / 24 ) ) );
    }
}
