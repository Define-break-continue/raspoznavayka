#ifndef RASPOZNAVAYKA_HEADER
#define RASPOZNAVAYKA_HEADER

#pragma once

#define __NIX__

#define SAMPLE_RATE 11025
#define SAMPLES_PER_FRAME 662
#define SAMPLES_PER_OVERLAP 0

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <string>
#include <typeinfo>

#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/source/WaveFile.h"
#include "aquila/source/FramesCollection.h"
#include "aquila/transform/Spectrogram.h"
#include "aquila/functions.h"


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

