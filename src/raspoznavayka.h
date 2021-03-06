#ifndef RASPOZNAVAYKA_HEADER
#define RASPOZNAVAYKA_HEADER

#pragma once

#define __NIX__

#define SAMPLE_RATE 11025
#define SAMPLES_PER_FRAME 2048
#define SAMPLES_PER_OVERLAP 0
#define LOWEST_NOTE Raspoznavayka::note_t::C
#define HIGHEST_NOTE Raspoznavayka::note_t::b3
#define LEVEL_ADDITION_N_OCTAVES 3 // > 0, n of octaves used in level addition for each note
#define HALFTONES_IN_AN_OCTAVE 12 // do not change
#define MAXIMUM_DIFFERENCE_OF_LEVEL_OF_TWO_NEAREST_NOTES 3 // need to find the proper value

#define LEVENSHTEIN_INSERT_COST 12
#define LEVENSHTEIN_DELETE_COST 12

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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "lib/aquila/global.h"
#include "lib/aquila/transform/FftFactory.h"
#include "lib/aquila/source/WaveFile.h"
#include "lib/aquila/source/FramesCollection.h"
#include "lib/aquila/transform/Spectrogram.h"
#include "lib/aquila/functions.h"
#include "lib/aquila/tools/TextPlot.h"

#include "errors.h"
#include "dB_t.h"

#include "CInputAudio.h"
#include "CInput.h"

#include "interval_t.h"
#include "CMelody.h"

#include "CHash.h"
#include "CFixedHash.h"

#include "CRecordedMelody.h"
#include "CIDTag.h"
#include "CInDBMelody.h"

#include "CHashMatch.h"
#include "math.h"

#include "CDataBase.h"

#endif // RASPOZNAVAYKA_HEADER

