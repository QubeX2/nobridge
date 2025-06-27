
#include "engine.h"

#include <iostream>

#include "card.h"
#include "deck.h"

namespace nobridge::engine {
    namespace output {
        void printCards(const CardL& cards) {
            std::cout << "CARDS\n";
            std::size_t i = 0;
            for (auto card : cards) {
                if (i > 0 && i % 13 == 0) {
                    std::cout << "\n";
                }
                std::cout << card << " ";
                i++;
            }
            std::cout << "\n\n";
        }

        void printDeal(const DealL& deal) {
            std::cout << "DEAL\n";
            for (auto hand : deal) {
                printCards(hand);
            }
        }

        void printDeck(const DeckPU& deck) {
            std::cout << "DECK\n";
            printCards(deck->cards());
        }
    }  // namespace output

}  // namespace nobridge::engine
