#include "card.h"

namespace nobridge::engine {

    Suit Card::suit() const { return m_suit; }

    void Card::setSuit(const Suit& newSuit) { m_suit = newSuit; }

}  // namespace nobridge::engine
