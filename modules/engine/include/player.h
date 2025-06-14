#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "card.h"

namespace nobridge::engine {

    enum class PlayerType { HUMAN = 1, COMPUTER = 2 };
    enum class Direction { NORTH = 1, EAST, SOUTH, WEST };

    class Player {
       public:
       private:
        PlayerType m_type;
        std::vector<Card> m_hand;
        Direction m_direction;
    };

}  // namespace nobridge::engine

#endif
