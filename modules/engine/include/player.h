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

    enum class PlayerType : uint8_t { HUMAN = 1, COMPUTER };
    enum class Direction : uint8_t { NORTH = 1, EAST, SOUTH, WEST };

    class Player {
       public:
        explicit Player(std::string name, PlayerType type, Direction direction,
                        HandPtr hand)
            : m_name(name),
              m_type(type),
              m_hand(hand),
              m_direction(direction) {}

        std::string name() { return m_name; }
        PlayerType type() { return m_type; }
        Direction direction() { return m_direction; }
        HandPtr hand() { return m_hand; }

       private:
        std::string m_name;
        PlayerType m_type;
        HandPtr m_hand;
        Direction m_direction;
    };

    using PlayerPtr = std::shared_ptr<Player>;
    using PlayerList = std::vector<PlayerPtr>;

    inline std::ostream& operator<<(std::ostream& os, const PlayerPtr& p) {
        os << std::fixed << std::setprecision(2);
        os << std::format("Name: {}, PlayerType: {}, Direction: {}\n",
                          p->name(), static_cast<uint8_t>(p->type()),
                          static_cast<uint8_t>(p->direction()));
        os << p->hand() << std::endl;
        return os;
    }
}  // namespace nobridge::engine

#endif
