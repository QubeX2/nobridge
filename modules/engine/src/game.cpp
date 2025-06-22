#include "game.h"

#include "player.h"

namespace nobridge::engine {

    void Game::addPlayer(PlayerPtr& player) { m_players.push_back(player); }

}  // namespace nobridge::engine
