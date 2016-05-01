#ifndef RASPOZNAVAYKA_HEADER
#define RASPOZNAVAYKA_HEADER

#pragma once

#define __NIX__

#define SAMPLE_RATE 11025
#define SAMPLES_PER_FRAME 1024
#define SAMPLES_PER_OVERLAP 0
#define LOWEST_NOTE Raspoznavayka::note_t::C
#define HIGHEST_NOTE Raspoznavayka::note_t::b3
#define LEVEL_ADDITION_N_OCTAVES 3 // > 0, n of octaves used in level addition for each note
#define NEEDED_HALFTONES_TO_THE_LAST_OBERTONE 24 // we need the energy of note freq and 2 upper octaves
#define HALFTONES_IN_AN_OCTAVE 12
#define MAXIMUM_DIFFERENCE_OF_LEVEL_OF_TWO_NEAREST_NOTES 3 // need to find the proper value

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <typeinfo>
#include <cmath>
#include <limits>

#include "lib/aquila/global.h"
#include "lib/aquila/transform/FftFactory.h"
#include "lib/aquila/source/WaveFile.h"
#include "lib/aquila/source/FramesCollection.h"
#include "lib/aquila/transform/Spectrogram.h"
#include "lib/aquila/functions.h"

#include "errors.h"
#include "dB_t.h"

#include "CInputAudio.h"

#include "interval_t.h"
#include "CMelody.h"

#include "CHash.h"
#include "CFixedHash.h"
#include "CHashMatch.h"

#include "CRecordedMelody.h"
#include "CIDTag.h"
#include "CInDBMelody.h"

#include "CDataBase.h"

#endif // RASPOZNAVAYKA_HEADER

