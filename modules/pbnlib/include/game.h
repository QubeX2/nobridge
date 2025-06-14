#ifndef PBN_GAME_H
#define PBN_GAME_H

#include <cstdint>
#include <string>

#include "auction.h"
#include "deal.h"
#include "play.h"

namespace nobridge::pbn {

    class Game {
       public:
       private:
        Deal m_deal;
        Auction m_auction;
        Play m_play;
        size_t m_board;
        std::string m_result;
        std::string m_declarer, m_contract;
        std::string m_scoring;
        std::string m_west, m_north, m_east, m_south;
        std::string m_event, m_site, m_date;
    };

}  // namespace nobridge::pbn

#endif
