#ifndef SCORE_ENGINE_H
#define SCORE_ENGINE_H

#include <cstdint>

#include "contract.h"
#include "types.h"
namespace nobridge::engine {

    namespace score {
        IntV calculate(const Contract& contract, UIntV tricks, bool vulnerable);

    }

}  // namespace nobridge::engine

#endif
