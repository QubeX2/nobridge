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
        std::vector<std::vector<std::shared_ptr<Card>>> deal();
        std::shared_ptr<Card> at(size_t index);

       private:
        std::array<std::shared_ptr<Card>, 52> m_cards;
    };

}  // namespace nobridge::engine

#endif
