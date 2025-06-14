#ifndef SCORE_ENGINE_H
#define SCORE_ENGINE_H

#include <cstdint>

#include "contract.h"
namespace nobridge::engine {

    using score_t = int16_t;
    using tricks_t = uint8_t;

    class ScoreEngine {
       public:
        score_t calculate(const Contract& contract, tricks_t tricks,
                          bool vulnerable);

       private:
    };

}  // namespace nobridge::engine

#endif
