#include "raspoznavayka.h"

CHash& CRecordedMelody::getHash() {
    return hash;
}

void CRecordedMelody::setHash() {
    hash = CHash( intervals );
}


