#ifndef ENGINE_HAND_H
#define ENGINE_HAND_H

#include <format>
#include <iomanip>
#include <ios>
#include <memory>

#include "card.h"
#include "types.h"

namespace nobridge::engine {

    /**
     * @brief Represents a player's hand of cards in a card game.
     *        This class manages the cards held by a player, allowing
     *        for operations such as adding, removing, and inspecting cards.
     */
    class Hand {
       public:
        Hand(CardL cards) : m_cards(std::move(cards)) {}
        const CardL& cards() const { return m_cards; }

        UIntA<HAND_LENGTH> toArray() const;
        float HCP();
        float distribution();
        // Get an array of counted suits [S,H,D,C] and ranks [2,3,4,5,6,7,8,9,T,J,Q,K,A]
        UIntA<4> suits();
        UIntA<13> ranks();

        // Count a specific rank from an array of counted ranks
        static UIntV rankCount(UIntA<13> list, Rank rank);
        // Get an Int from a Card
        static UIntV toInt(const CardPU& card);
        // Get a CardP from an integer
        static CardPU toCard(const UIntV num);

       private:
        CardL m_cards;
    };

    inline std::ostream& operator<<(std::ostream& os, const HandPU& h) {
        os << std::fixed << std::setprecision(2);
        os << "Hand\n";
        std::size_t i = 0;
        for (const CardPU& card : h->cards()) {
            if (i > 0 && i % 13 == 0) {
                os << "\n";
            }
            os << card << " ";
            i++;
        }
        os << "\n";
        return os;
    }
}  // namespace nobridge::engine

#endif
