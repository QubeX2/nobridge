#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "deck.h"
#include "types.h"

namespace nobridge::engine {
    namespace output {
        void printCards(const CardL& cards);
        void printDeal(const DealL& deal);
        void printDeck(const DeckPU& deck);
    }  // namespace output

}  // namespace nobridge::engine

#endif
