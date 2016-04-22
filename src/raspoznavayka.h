#ifndef RASPOZNAVAYKA_HEADER
#define RASPOZNAVAYKA_HEADER

#pragma once

#define __NIX__

#define SAMPLE_RATE 11025
#define SAMPLES_PER_FRAME 1024
#define SAMPLES_PER_OVERLAP 0
#define LOWEST_NOTE C
#define HIGHEST_NOTE b3
#define NEEDED_HALFTONES_TO_THE_LAST_OBERTONE 24 // we need the energy of note freq and 2 upper octaves
#define HALFTONES_IN_AN_OCTAVE 12

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

#include "lib/aquila/global.h"
#include "lib/aquila/transform/FftFactory.h"
#include "lib/aquila/source/WaveFile.h"
#include "lib/aquila/source/FramesCollection.h"
#include "lib/aquila/transform/Spectrogram.h"
#include "lib/aquila/functions.h"

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

