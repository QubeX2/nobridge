#ifndef BRIDGE_ENGINE_H
#define BRIDGE_ENGINE_H

#include <array>
#include <cstdint>
#include <memory>

#include "bidengine.h"
#include "deck.h"
#include "playengine.h"
#include "player.h"
#include "scoreengine.h"
namespace nobridge::engine {

    class BridgeEngine {
       public:
        auto getPlayers() { return m_players; }
        void addPlayer(std::shared_ptr<Player>& player);

       private:
        Deck m_deck;
        std::array<std::shared_ptr<Player>, 4> m_players;
        BidEngine m_bids;
        PlayEngine m_play;
        ScoreEngine m_scoring;
    };

}  // namespace nobridge::engine

#endif
