#ifndef ENGINE_HAND_H
#define ENGINE_HAND_H

#include <memory>
#include <vector>

#include "card.h"
namespace nobridge::engine {

    class Hand {
       public:
        Hand(CardList cards, bool dealer = false, bool vulnerable = false)
            : m_cards(cards), m_dealer(dealer), m_vulnerable(vulnerable) {}

        CardList cards() { return m_cards; }
        bool dealer() { return m_dealer; }
        bool vulnerable() { return m_vulnerable; }

       private:
        CardList m_cards;
        bool m_dealer;
        bool m_vulnerable;
    };

    using HandPtr = std::shared_ptr<Hand>;
    using HandList = std::vector<HandPtr>;

}  // namespace nobridge::engine

#endif
