#ifndef TRICK_H
#define TRICK_H

#include "card.h"
#include "player.h"
#include <memory>
#include <vector>

namespace  nobridge::engine {

class Trick {
  std::shared_ptr<Player> m_leader;
  std::vector<std::shared_ptr<Card>> m_cards;

public:
  void add_card(std::shared_ptr<Card>& card);
  void add_card(std::shared_ptr<Card>& card, std::shared_ptr<Player>& player);
  // get_winner??
};

}

#endif
