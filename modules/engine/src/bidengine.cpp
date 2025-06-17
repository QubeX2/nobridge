#include "bidengine.h"

#include <sys/types.h>

#include <cstdint>
#include <memory>

#include "bridgeengine.h"
#include "player.h"

namespace nobridge::engine {

    void BridgeEngine::addPlayer(PlayerPtr& player) {
        for (uint i = 0; i < m_players.size(); i++) {
            if (m_players[i] == nullptr) {
                m_players[i] = player;
            }
        }
    }

}  // namespace nobridge::engine
