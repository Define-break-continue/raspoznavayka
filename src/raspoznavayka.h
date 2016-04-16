#ifndef RASPOZNAVAYKA_HEADER
#define RASPOZNAVAYKA_HEADER

#define __NIX__
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <string>
#include <typeinfo>

#include "lib/aquila/global.h"
#include "lib/aquila/transform/FftFactory.h"
#include "lib/aquila/source/WaveFile.h"

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

