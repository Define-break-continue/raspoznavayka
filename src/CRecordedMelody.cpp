#include "CRecordedMelody.h"

CHash& CRecordedMelody::getHash() {
    return hash;
}

void CRecordedMelody::setHash() {
    hash = CHash( intervals );
}


