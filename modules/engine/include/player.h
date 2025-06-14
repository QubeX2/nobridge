#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <memory>
#include <vector>

namespace  nobridge::engine {

enum class PlayerType { HUMAN = 1, COMPUTER = 2 };
enum class Direction { NORTH = 1, EAST, SOUTH, WEST };

class Player {
  PlayerType m_type;
  std::vector<std::shared_ptr<Card>> m_hand;
  Direction m_direction;
  
public:

};

}

#endif
