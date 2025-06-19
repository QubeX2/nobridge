#include "card.h"

#include <algorithm>
#include <cstdint>
#include <format>
#include <iostream>

namespace nobridge::engine {

    Suit Card::suit() const { return m_suit; }
    void Card::setSuit(const Suit& newSuit) { m_suit = newSuit; }
    Rank Card::rank() const { return m_rank; }
    void Card::setRank(const Rank& newRank) { m_rank = newRank; }

    std::string Card::toString() {
        return std::format("{}{}\033[0m", m_suit_texts[m_suit],
                           m_rank_texts[m_rank]);
    }

    namespace card {
        UIntArray4 countSuits(const CardList& cards) {
            UIntArray4 handcount{0, 0, 0, 0};
            for (const CardPtr& card : cards) {
                handcount[static_cast<uint8_t>(card->suit()) - 1]++;
            }
            for (auto n : handcount) {
                std::println("N: {}", n);
            }
            return handcount;
        }

        uint8_t calculateHCP(const CardList& cards) {}

    }  // namespace card
}  // namespace nobridge::engine
