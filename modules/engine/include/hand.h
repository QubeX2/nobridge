#ifndef ENGINE_HAND_H
#define ENGINE_HAND_H

#include <format>
#include <iomanip>
#include <ios>
#include <memory>

#include "card.h"
#include "types.h"

namespace nobridge::engine {

    class Hand {
       public:
        Hand(CardL cards, bool dealer = false, bool vulnerable = false)
            : m_cards(cards), m_dealer(dealer), m_vulnerable(vulnerable) {}

        CardL cards() { return m_cards; }
        bool dealer() { return m_dealer; }
        bool vulnerable() { return m_vulnerable; }

       private:
        CardL m_cards;
        bool m_dealer;
        bool m_vulnerable;
    };

    inline std::ostream& operator<<(std::ostream& os, const HandPU& h) {
        os << std::fixed << std::setprecision(2);
        os << std::format("Dealer: {}, Vulnerable: {}\n", static_cast<bool>(h->dealer()),
                          static_cast<bool>(h->vulnerable()));
        std::size_t i = 0;
        for (auto card : h->cards()) {
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
