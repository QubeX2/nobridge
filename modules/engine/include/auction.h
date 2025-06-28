#ifndef ENGINE_AUCTION_H
#define ENGINE_AUCTION_H

#include <format>
#include <iomanip>
#include <iostream>

#include "bid.h"
#include "types.h"

namespace nobridge::engine {

    class Auction {
       public:
        void setDirection(const Direction& direction) { m_direction = direction; }
        void addBid(BidA bids) { m_bids.push_back(std::move(bids)); }
        const BidL& bids() const { return m_bids; }
        Direction direction() const { return m_direction; }

       private:
        BidL m_bids;
        Direction m_direction;
    };

    inline std::ostream& operator<<(std::ostream& os, const AuctionPU& a) {
        os << std::fixed << std::setprecision(2);
        os << "Auction - Direction: " << a->direction() << "\n";
        UIntV dir = static_cast<UIntV>(a->direction());
        const static StringA<4> dirs{"N", "E", "S", "W"};
        UIntV ix = dir - 1;
        for (const BidA& bid : a->bids()) {
            for (UIntV i = 0; i < 4; i++) {
                if (bid[i] != nullptr) {
                    if (bid[i]->denomination() == Denomination::PASS) {
                        os << dirs[ix] << ":" << "Pass ";
                    } else {
                        os << dirs[ix] << ":" << static_cast<int>(bid[i]->level())
                           << bid[i]->denomination() << bid[i]->risk() << " ";
                    }
                    ix = (ix + 1) % 4;
                }
            }
            std::cout << "\n";
        }
        return os;
    }
}  // namespace nobridge::engine

#endif
