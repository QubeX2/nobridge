#ifndef CONTRACT_H
#define CONTRACT_H

#include <cstdint>
#include <memory>

#include "bid.h"
#include "card.h"
#include "player.h"
#include "types.h"

namespace nobridge::engine {

    class Contract {
        UIntVal m_level;
        Suit m_suit;
        // doubled??
        PlayerPtr m_declarer;

       public:
    };

}  // namespace nobridge::engine
#endif
