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
#include "types.h"

namespace nobridge::engine {

    class Game {
       public:
        const PlayerM& players() const { return m_players; }
        const PlayPU& play() const { return m_play; }
        void addPlayer(Direction direction, PlayerPU& player) { m_players.emplace(direction, std::move(player)); }
        void addPlay(PlayPU& play) { m_play = std::move(play); }

       private:
        std::string m_event;
        std::string m_site;
        std::string m_date;
        std::size_t m_board;
        PlayerM m_players;
        PlayPU m_play;
    };

    inline std::ostream& operator<<(std::ostream& os, const GamePU& g) {
        os << std::fixed << std::setprecision(2);
        os << std::format("Players: {}\n", g->players().size());
        for (auto direction : DIRECTION_L) {
            os << direction << ": " << g->players().at(direction) << "\n";
        }
        if (g->play() != nullptr) {
            os << g->play() << "\n";
        }
        return os;
    }
}  // namespace nobridge::engine

#endif
