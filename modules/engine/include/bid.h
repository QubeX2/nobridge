#ifndef ENGINE_BID_H
#define ENGINE_BID_H

#include <cstdint>
#include <memory>

#include "card.h"
#include "player.h"
#include "types.h"

namespace nobridge::engine {

    class Bid {
       public:
       private:
        UIntV m_level{};
        Denomination m_denomination;
        Risk m_risk;
    };

}  // namespace nobridge::engine

#endif
