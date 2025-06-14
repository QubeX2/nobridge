#ifndef SCORE_ENGINE_H
#define SCORE_ENGINE_H

#include <cstdint>

#include "contract.h"
namespace nobridge::engine {

    class ScoreEngine {
       public:
        int16_t calculate(const Contract& contract, uint8_t tricks,
                          bool vulnerable);

       private:
    };

}  // namespace nobridge::engine

#endif
