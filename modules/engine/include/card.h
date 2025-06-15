#ifndef CARD_H
#define CARD_H

#include <cstdint>
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
        Suit suit() const;
        void setSuit(const Suit& newSuit);

       private:
        Suit m_suit;
        Rank m_rank;
    };

}  // namespace nobridge::engine

#endif
