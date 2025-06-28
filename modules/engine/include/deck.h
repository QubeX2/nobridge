#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>

#include "types.h"

namespace nobridge::engine {

    class Deck {
       public:
        Deck();
        const CardL& cards() const { return m_cards; }

        void shuffle();
        // 4 deals with 13 cards
        DealL deal();
        const Card* at(const size_t& index);

       private:
        CardL m_cards;
    };

}  // namespace nobridge::engine

#endif
