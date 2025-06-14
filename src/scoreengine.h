#ifndef NOB_SCORE_ENGINE_H
#define NOB_SCORE_ENGINE_H

#include "contract.h"
#include <cstdint>
namespace nobridge {

using score_t = int16_t;
using tricks_t = uint8_t;

class ScoreEngine {

public:
  score_t calculate(const Contract& contract, tricks_t tricks, bool vulnerable);
};

}

#endif
