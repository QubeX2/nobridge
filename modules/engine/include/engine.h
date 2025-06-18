#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "card.h"
#include "deck.h"

namespace nobridge::engine {
    namespace output {
        void printCards(const CardList& cards);
        void printDeal(const DealList& deal);
        void printDeck(const DeckPtr& deck);
    }  // namespace output

}  // namespace nobridge::engine

#endif
