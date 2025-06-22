#ifndef SCORE_ENGINE_H
#define SCORE_ENGINE_H

#include <cstdint>

#include "contract.h"
namespace nobridge::engine {

    namespace score {
        int16_t calculate(const Contract& contract, uint8_t tricks,
                          bool vulnerable);

    }

}  // namespace nobridge::engine

#endif
