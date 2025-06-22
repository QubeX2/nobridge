#ifndef CONTRACT_H
#define CONTRACT_H

#include <cstdint>
#include <memory>

#include "bid.h"
#include "card.h"
#include "player.h"

namespace nobridge::engine {

    class Contract {
        uint8_t m_level;
        Suit m_suit;
        // doubled??
        PlayerPtr m_declarer;

       public:
    };

    using ContractPtr = std::shared_ptr<Contract>;
}  // namespace nobridge::engine
#endif
