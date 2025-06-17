#include "trick.h"

#include <cstddef>
#include <memory>

#include "player.h"

namespace nobridge::engine {

    void Trick::addCard(CardPtr& card) { m_cards.push_back(card); }
    void Trick::addCard(CardPtr& card, PlayerPtr& player) {
        this->addCard(card);
        if (m_leader == nullptr) {
            m_leader = player;
        }
    }

}  // namespace nobridge::engine
