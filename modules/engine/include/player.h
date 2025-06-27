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
        explicit Player(std::string name, PlayerType type, HandPU hand)
            : m_name(std::move(name)), m_type(type), m_hand(std::move(hand)) {}

        std::string name() { return m_name; }
        PlayerType type() { return m_type; }
        const HandPU& hand() const { return m_hand; }

       private:
        std::string m_name;
        PlayerType m_type;
        HandPU m_hand;
    };

    inline std::ostream& operator<<(std::ostream& os, const PlayerPU& p) {
        os << std::fixed << std::setprecision(2);
        os << p->name() << "\n";
        os << p->hand() << "\n";
        return os;
    }
}  // namespace nobridge::engine

#endif
