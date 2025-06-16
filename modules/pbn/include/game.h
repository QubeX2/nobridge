#ifndef PBN_GAME_H
#define PBN_GAME_H

#include <cstdint>
#include <string>

#include "auction.h"
#include "deal.h"
#include "play.h"

namespace nobridge::pbn {

    struct Game {
        Deal deal;
        Auction auction;
        Play play;
        size_t board;
        std::string result;
        std::string declarer, contract;
        std::string scoring;
        std::string west, north, east, south;
        std::string event, site, date;
    };

}  // namespace nobridge::pbn

#endif
