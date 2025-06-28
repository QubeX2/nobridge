#ifndef ENGINE_PLAY_H
#define ENGINE_PLAY_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "bid.h"
#include "contract.h"
#include "deck.h"
#include "player.h"
#include "types.h"

namespace nobridge::engine {

    class Play {
       public:
        void setDirection(const Direction& direction) { m_direction = direction; }
        void addTrick(TrickA tricks) { m_tricks.push_back(std::move(tricks)); }
        const TrickL& tricks() const { return m_tricks; }
        Direction direction() const { return m_direction; }

       private:
        Direction m_direction;
        TrickL m_tricks;
    };

    inline std::ostream& operator<<(std::ostream& os, const PlayPU& p) {
        os << std::fixed << std::setprecision(2);
        os << "Play - Direction: " << p->direction() << "\n";
        UIntV dir = static_cast<UIntV>(p->direction());
        const static StringA<4> dirs{"N", "E", "S", "W"};
        UIntV ix = dir - 1;
        int tno = 1;
        for (const TrickA& trick : p->tricks()) {
            std::cout << "Trick" << std::setfill('0') << std::setw(2) << (tno++) << " ";
            for (UIntV i = 0; i < 4; i++) {
                if (trick[i] != nullptr) {
                    std::cout << dirs[ix] << ":" << trick[i] << " ";
                    ix = (ix + 1) % 4;
                }
            }
            std::cout << "\n";
        }
        return os;
    }

}  // namespace nobridge::engine

#endif
