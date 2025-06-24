#include "card.h"

#include <algorithm>
#include <cstdint>
#include <format>
#include <iostream>

#include "types.h"

namespace nobridge::engine {

    Suit Card::suit() const { return m_suit; }
    void Card::setSuit(const Suit& suit) { m_suit = suit; }
    Rank Card::rank() const { return m_rank; }
    void Card::setRank(const Rank& rank) { m_rank = rank; }
    void Card::setSuitAndRank(const Suit& suit, const Rank& rank) {
        this->setSuit(suit);
        this->setRank(rank);
    }

}  // namespace nobridge::engine
