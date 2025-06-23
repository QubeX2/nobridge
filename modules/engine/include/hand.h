#ifndef ENGINE_HAND_H
#define ENGINE_HAND_H

#include <format>
#include <iomanip>
#include <ios>
#include <memory>
#include <set>
#include <vector>

#include "card.h"
namespace nobridge::engine {

    class Hand {
       public:
        Hand(CardList cards, bool dealer = false, bool vulnerable = false)
            : m_cards(cards), m_dealer(dealer), m_vulnerable(vulnerable) {}

        CardList cards() { return m_cards; }
        bool dealer() { return m_dealer; }
        bool vulnerable() { return m_vulnerable; }

       private:
        CardList m_cards;
        bool m_dealer;
        bool m_vulnerable;
    };

    using HandPtr = std::shared_ptr<Hand>;
    using HandList = std::vector<HandPtr>;

    inline std::ostream& operator<<(std::ostream& os, const HandPtr& h) {
        os << std::fixed << std::setprecision(2);
        os << std::format("Dealer: {}, Vulnerable: {}\n",
                          static_cast<bool>(h->dealer()),
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
