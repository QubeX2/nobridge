#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include "bid.h"
#include "contract.h"
#include "deck.h"
#include "play.h"
#include "player.h"
#include "trick.h"

namespace nobridge::engine {

    class Game {
       public:
        auto players() { return m_players; }
        void addPlayer(PlayerPtr& player);

       private:
        std::string m_event;
        std::string m_site;
        std::string m_date;
        std::size_t m_board;
        ContractPtr m_contract;
        PlayerList m_players;
        BidList m_bids;
        Play m_play;
    };

    inline std::ostream& operator<<(std::ostream& os, const GamePtr& g) {
        os << std::fixed << std::setprecision(2);
        os << std::format("Players: {}\n", g->players().size());
        for (auto p : g->players()) {
            os << p << "\n";
        }
        return os;
    }
}  // namespace nobridge::engine

#endif
