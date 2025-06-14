#ifndef NOB_BID_ENGINE_H
#define NOB_BID_ENGINE_H

#include "bid.h"
#include <memory>
#include <vector>

namespace nobridge {

class BidEngine {
  std::vector<std::shared_ptr<Bid>> m_history;

public:
};

}

#endif
