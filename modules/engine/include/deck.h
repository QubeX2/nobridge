#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>

#include "card.h"

namespace nobridge::engine {

    class Deck {
       public:
        void shuffle();
        std::vector<std::vector<std::shared_ptr<Card>>> deal();

       private:
        std::vector<std::shared_ptr<Card>> m_cards;
    };

}  // namespace nobridge::engine

#endif
