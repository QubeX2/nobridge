#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include "bid.h"
#include "contract.h"
#include "deck.h"
#include "player.h"
#include "trick.h"
namespace nobridge::engine {

    class Game {
       public:
        auto getPlayers() { return m_players; }
        void addPlayer(PlayerPtr& player);

       private:
        ContractPtr m_contract;
        PlayerList m_players;
        BidList m_bids;
        TrickList m_tricks;
    };

    using GamePtr = std::shared_ptr<Game>;
    using GameList = std::vector<GamePtr>;

}  // namespace nobridge::engine

#endif
