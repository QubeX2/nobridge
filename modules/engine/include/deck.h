#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>

#include "card.h"

namespace nobridge::engine {

    class Deck {
       public:
        void shuffle();
        // 4 deals with 13 cards
        std::vector<std::vector<Card>> deal();

       private:
        std::vector<Card> m_cards;
    };

}  // namespace nobridge::engine

#endif
