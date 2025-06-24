#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>

#include "types.h"

namespace nobridge::engine {

    class Deck {
       public:
        Deck();

        CardList cards() { return m_cards; }
        CardList cards() const { return m_cards; }

        void shuffle();
        // 4 deals with 13 cards
        DealList deal();
        CardPtr at(size_t index);

       private:
        CardList m_cards;
    };

}  // namespace nobridge::engine

#endif
