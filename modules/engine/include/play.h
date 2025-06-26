#ifndef ENGINE_PLAY_H
#define ENGINE_PLAY_H

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include "bid.h"
#include "contract.h"
#include "deck.h"
#include "player.h"
#include "trick.h"
#include "types.h"

namespace nobridge::engine {

    class Play {
       public:
        void setDirection(const Direction& direction);
        void addTrick(const TrickArray& trick);
        TrickList tricks();
        Direction direction();

       private:
        Direction m_direction;
        TrickList m_tricks;
    };

}  // namespace nobridge::engine

#endif
