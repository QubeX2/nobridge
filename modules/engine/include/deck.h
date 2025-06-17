#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>

#include "card.h"

namespace nobridge::engine {

    class Deck {
       public:
        Deck();

        void shuffle();
        void print();
        // 4 deals with 13 cards
        std::vector<CardList> deal();
        CardPtr at(size_t index);

       private:
        CardList m_cards;
    };

    using DeckPtr = std::shared_ptr<Deck>;

}  // namespace nobridge::engine

#endif
