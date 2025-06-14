#ifndef CARD_H
#define CARD_H

namespace nobridge::engine {

enum class Suit { CLUBS = 1, DIAMONDS, HEARTS, SPADES };
enum class Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

class Card {
  Suit m_suit;
  Rank m_rank;

public:
};

}

#endif
