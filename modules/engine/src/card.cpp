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

}  // namespace nobridge::engine
