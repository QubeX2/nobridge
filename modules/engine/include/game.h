#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include <array>
#include <cstdint>
#include <format>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>

#include "auction.h"
#include "bid.h"
#include "contract.h"
#include "deck.h"
#include "play.h"
#include "player.h"
#include "types.h"

namespace nobridge::engine {

    class Game {
       public:
        Game()
            : m_event(""),
              m_site(""),
              m_date(""),
              m_board(0),
              m_dealer(Direction::NONE),
              m_vulnerable(Vulnerable::NONE) {}
        const PlayerM& players() const { return m_players; }
        const PlayerPU& getPlayer(Direction direction) const { return m_players.at(direction); }
        const PlayPU& play() const { return m_play; }
        const AuctionPU& auction() const { return m_auction; }
        const ContractPU& contract() const { return m_contract; }
        Direction dealer() const { return m_dealer; }
        Vulnerable vulnerable() const { return m_vulnerable; }

        void addPlayer(Direction direction, PlayerPU player) {
            m_players.emplace(direction, std::move(player));
        }
        void setPlay(PlayPU play) { m_play = std::move(play); }
        void setAuction(AuctionPU auction) { m_auction = std::move(auction); }
        void setContract(ContractPU contract) { m_contract = std::move(contract); }
        void setDealer(Direction dealer) { m_dealer = dealer; }
        void setVulnerable(Vulnerable vulnerable) { m_vulnerable = vulnerable; }

       private:
        std::string m_event;
        std::string m_site;
        std::string m_date;
        std::size_t m_board;
        Direction m_dealer;
        Vulnerable m_vulnerable;
        PlayerM m_players;
        PlayPU m_play;
        AuctionPU m_auction;
        ContractPU m_contract;
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
        os << g->contract() << "\n";
        os << g->auction() << "\n";
        return os;
    }
}  // namespace nobridge::engine

#endif
