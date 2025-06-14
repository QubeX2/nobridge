#ifndef PBN_AUCTION_H
#define PBN_AUCTION_H

#include <string>
#include <vector>
namespace nobridge::pbn {

    class Auction {
       public:
       private:
        std::string m_auction;
        std::vector<std::string> m_bids;
    };

}  // namespace nobridge::pbn

#endif
