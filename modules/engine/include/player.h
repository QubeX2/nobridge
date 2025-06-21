#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "card.h"
#include "hand.h"

namespace nobridge::engine {

    enum class PlayerType : uint8_t { HUMAN = 1, COMPUTER = 2 };
    enum class Direction : uint8_t { WEST = 1, NORTH, EAST, SOUTH };

    class Player {
       public:
       private:
        PlayerType m_type;
        Hand m_hand;
        Direction m_direction;
    };

    using PlayerPtr = std::shared_ptr<Player>;
    using PlayerList = std::vector<PlayerPtr>;

}  // namespace nobridge::engine

#endif
