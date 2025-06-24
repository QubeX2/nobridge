#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <format>
#include <iomanip>
#include <ios>
#include <memory>

#include "hand.h"
#include "types.h"

namespace nobridge::engine {

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

    inline std::ostream& operator<<(std::ostream& os, const PlayerPtr& p) {
        os << std::fixed << std::setprecision(2);
        os << std::format("Name: {}, PlayerType: {}, Direction: {}\n",
                          p->name(), static_cast<UIntVal>(p->type()),
                          static_cast<UIntVal>(p->direction()));
        os << p->hand() << "\n";
        return os;
    }
}  // namespace nobridge::engine

#endif
