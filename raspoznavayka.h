#ifndef RASPOZNAVAYKA_HEADER
#define RASPOZNAVAYKA_HEADER

/*
 * mel_size_t is a type to store length and offsets
 * of interval structures, representing melodies.
 */
#define _mel_size_t uint16_t
/*
 * up & down arrows for CHash
 */
#define _arrow_up 1
#define _arrow_down 0

#define __NIX__
#include <iostream>
#include <fstream>
#include <cstdint>
#include <assert.h>
#include <vector>
#include "CMelody.h"
#include "CHash.h"
#include "CFixedHash.h"
#include "CInDBMelody.h"
#include "CHashMatch.h"
#include "CDataBase.h"

#endif // RASPOZNAVAYKA_HEADER

