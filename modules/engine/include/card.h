#ifndef CARD_H
#define CARD_H

#include <array>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nobridge::engine {

    enum class Suit : uint8_t { SPADES = 1, HEARTS, DIAMONDS, CLUBS };
    enum class Rank : uint8_t {
        TWO = 2,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE
    };

    const std::array<Suit, 4> kCardSuitList{Suit::SPADES, Suit::HEARTS,
                                            Suit::DIAMONDS, Suit::CLUBS};

    class Card {
       public:
        Card(Suit s, Rank r) : m_suit(s), m_rank(r) {}
        Suit suit() const;
        void setSuit(const Suit& newSuit);
        Rank rank() const;
        void setRank(const Rank& newRank);

        std::string toString();

       private:
        std::map<Suit, std::string> m_suit_texts{{Suit::SPADES, "\033[35m♠"},
                                                 {Suit::HEARTS, "\033[31m♥"},
                                                 {Suit::DIAMONDS, "\033[31m♦"},
                                                 {Suit::CLUBS, "\033[32m♣"}};
        std::map<Rank, std::string> m_rank_texts{
            {Rank::TWO, "2"},   {Rank::THREE, "3"}, {Rank::FOUR, "4"},
            {Rank::FIVE, "5"},  {Rank::SIX, "6"},   {Rank::SEVEN, "7"},
            {Rank::EIGHT, "8"}, {Rank::NINE, "9"},  {Rank::TEN, "T"},
            {Rank::JACK, "J"},  {Rank::QUEEN, "Q"}, {Rank::KING, "K"},
            {Rank::ACE, "A"}};
        Suit m_suit;
        Rank m_rank;
    };

    using CardPtr = std::shared_ptr<Card>;
    using CardList = std::vector<CardPtr>;

}  // namespace nobridge::engine

#endif
