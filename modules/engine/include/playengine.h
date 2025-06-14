#ifndef PLAY_ENGINE_H
#define PLAY_ENGINE_H

#include "trick.h"
#include <memory>
#include <vector>
namespace nobridge::engine {

class PlayEngine {
  std::vector<std::shared_ptr<Trick>> m_tricks;

public:

};

}

#endif
