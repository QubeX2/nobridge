#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "card.h"

namespace nobridge::engine {

    enum class PlayerType : uint8_t { HUMAN = 1, COMPUTER = 2 };
    enum class Direction : uint8_t { WEST = 1, NORTH, EAST, SOUTH };

    class Player {
       public:
       private:
        PlayerType m_type;
        std::vector<Card> m_hand;
        Direction m_direction;
    };

}  // namespace nobridge::engine

#endif
