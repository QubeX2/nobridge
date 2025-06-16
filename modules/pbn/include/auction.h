#ifndef PBN_AUCTION_H
#define PBN_AUCTION_H

#include <string>
#include <vector>
namespace nobridge::pbn {

    struct Auction {
        std::string auction;
        std::vector<std::string> bids;
    };

}  // namespace nobridge::pbn

#endif
