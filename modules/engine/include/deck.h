#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>

#include "types.h"

namespace nobridge::engine {

    class Deck {
       public:
        Deck();

        CardL cards() { return m_cards; }
        CardL cards() const { return m_cards; }

        void shuffle();
        // 4 deals with 13 cards
        DealL deal();
        CardP at(size_t index);

       private:
        CardL m_cards;
    };

}  // namespace nobridge::engine

#endif
