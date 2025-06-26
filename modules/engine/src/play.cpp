
#include "play.h"

#include "types.h"

namespace nobridge::engine {

    Direction Play::direction() { return m_direction; }
    void Play::setDirection(const Direction& direction) {
        m_direction = direction;
    }
    TrickList Play::tricks() { return m_tricks; }
    void Play::addTrick(const TrickArray& trick) { m_tricks.push_back(trick); }

}  // namespace nobridge::engine
