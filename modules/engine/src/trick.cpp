#include "trick.h"
#include "player.h"
#include <cstddef>
#include <memory>

namespace nobridge::engine {

void Trick::add_card(std::shared_ptr<Card>& card) 
{
  m_cards.push_back(card);
}

void Trick::add_card(std::shared_ptr<Card>& card, std::shared_ptr<Player>& player) 
{
  this->add_card(card);
  if(m_leader == nullptr) {
    m_leader = player;
  }
}

}
