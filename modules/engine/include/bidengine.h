#ifndef BID_ENGINE_H
#define BID_ENGINE_H

#include <memory>
#include <vector>

#include "bid.h"

namespace nobridge::engine {

    class BidEngine {
       public:
       private:
        std::vector<Bid> m_history;
    };

}  // namespace nobridge::engine

#endif
