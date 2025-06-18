#ifndef CARD_H
#define CARD_H

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nobridge::engine {

    enum class Suit : uint8_t { CLUBS = 1, DIAMONDS, HEARTS, SPADES };
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

    class Card {
       public:
        Card(Suit s, Rank r) : m_suit(s), m_rank(r) {}
        Suit suit() const;
        void setSuit(const Suit& newSuit);
        Rank rank() const;
        void setRank(const Rank& newRank);

        std::string toString();

       private:
        std::map<Suit, std::string> m_suit_texts{{Suit::CLUBS, "\033[32m♣"},
                                                 {Suit::DIAMONDS, "\033[31m♦"},
                                                 {Suit::HEARTS, "\033[31m♥"},
                                                 {Suit::SPADES, "\033[35m♠"}};
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
