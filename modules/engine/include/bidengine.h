#ifndef BID_ENGINE_H
#define BID_ENGINE_H

#include "bid.h"
#include <memory>
#include <vector>

namespace nobridge::engine {

class BidEngine {
  std::vector<std::shared_ptr<Bid>> m_history;

public:
};

}

#endif
