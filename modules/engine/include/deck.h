#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <memory>
#include <vector>

namespace nobridge::engine {

class Deck {
  std::vector<std::shared_ptr<Card>> m_cards;

public:
  void shuffle();
  std::vector<std::vector<std::shared_ptr<Card>>> deal();
};

}

#endif
