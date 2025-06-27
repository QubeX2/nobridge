#ifndef CARD_H
#define CARD_H

#include <cstdint>
#include <format>
#include <iomanip>
#include <ios>
#include <memory>
#include <string>
#include <vector>

#include "types.h"

namespace nobridge::engine {
    class Card {
       public:
        Card(Suit s, Rank r) : m_suit(s), m_rank(r) {}
        Suit suit() const { return m_suit; }
        void setSuit(const Suit& suit) { m_suit = suit; }
        Rank rank() const { return m_rank; }
        void setRank(const Rank& rank) { m_rank = rank; }
        void setSuitAndRank(const Suit& suit, const Rank& rank) {
            this->m_suit = suit;
            this->m_rank = rank;
        }

        std::string rankText() { return m_rank_texts[m_rank]; }
        std::string suitText() { return m_suit_texts[m_suit]; }

       private:
        Suit m_suit;
        Rank m_rank;

        LegendM<Suit> m_suit_texts{{Suit::SPADES, ansi::fg::MAGENTA + "♠"},
                                   {Suit::HEARTS, ansi::fg::RED + "♥"},
                                   {Suit::DIAMONDS, ansi::fg::YELLOW + "♦"},
                                   {Suit::CLUBS, ansi::fg::GREEN + "♣"}};
        LegendM<Rank> m_rank_texts{{Rank::TWO, "2"}, {Rank::THREE, "3"}, {Rank::FOUR, "4"},  {Rank::FIVE, "5"},
                                   {Rank::SIX, "6"}, {Rank::SEVEN, "7"}, {Rank::EIGHT, "8"}, {Rank::NINE, "9"},
                                   {Rank::TEN, "T"}, {Rank::JACK, "J"},  {Rank::QUEEN, "Q"}, {Rank::KING, "K"},
                                   {Rank::ACE, "A"}};
    };

    inline std::ostream& operator<<(std::ostream& os, const CardP& c) {
        os << std::fixed << std::setprecision(2);
        os << std::format("{}{}\033[0m", c->suitText(), c->rankText());
        return os;
    }
}  // namespace nobridge::engine

#endif
