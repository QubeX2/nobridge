#include "bidengine.h"
#include "bridgeengine.h"
#include "player.h"
#include <cstdint>
#include <memory>
#include <sys/types.h>

namespace nobridge::engine {

void BridgeEngine::add_player(std::shared_ptr<Player>& player) 
{
  for(uint i = 0; i < m_players.size(); i++) {
    if(m_players[i] == nullptr) {
      m_players[i] = player;
    }
  }
} 

}
