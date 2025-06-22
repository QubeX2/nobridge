#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <format>
#include <iomanip>
#include <ios>
#include <memory>
#include <vector>

#include "card.h"
#include "hand.h"

namespace nobridge::engine {

    enum class PlayerType : uint8_t { HUMAN = 1, COMPUTER = 2 };
    enum class Direction : uint8_t { WEST = 1, NORTH, EAST, SOUTH };

    class Player {
       public:
        explicit Player(PlayerType type, Direction direction, HandPtr hand)
            : m_type(type), m_hand(hand), m_direction(direction) {}

        PlayerType type() { return m_type; }
        Direction direction() { return m_direction; }
        HandPtr hand() { return m_hand; }

       private:
        PlayerType m_type;
        HandPtr m_hand;
        Direction m_direction;
    };

    using PlayerPtr = std::shared_ptr<Player>;
    using PlayerList = std::vector<PlayerPtr>;

    inline std::ostream& operator<<(std::ostream& os, const PlayerPtr& p) {
        os << std::fixed << std::setprecision(2);
        os << std::format("PlayerType: {}, Direction {}",
                          static_cast<uint8_t>(p->type()),
                          static_cast<uint8_t>(p->direction()));
        return os;
    }
}  // namespace nobridge::engine

#endif
