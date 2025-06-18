
#include "engine.h"

#include <iostream>

#include "card.h"
#include "deck.h"

namespace nobridge::engine {
    namespace output {
        void printCards(const CardList& cards) {
            std::cout << "CARDS" << std::endl;
            std::size_t i = 0;
            for (auto card : cards) {
                if (i++ % 13 == 0) std::cout << std::endl;
                std::cout << card->toString() << " ";
            }
            std::cout << std::endl;
        }

        void printDeal(const DealList& deal) {
            std::cout << "DEAL" << std::endl;
            for (auto hand : deal) {
                printCards(hand);
            }
        }

        void printDeck(const DeckPtr& deck) {
            std::cout << "DECK" << std::endl;
            printCards(deck->cards());
        }
    }  // namespace output

}  // namespace nobridge::engine
