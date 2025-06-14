#ifndef PLAY_ENGINE_H
#define PLAY_ENGINE_H

#include <memory>
#include <vector>

#include "trick.h"
namespace nobridge::engine {

    class PlayEngine {
       public:
       private:
        std::vector<Trick> m_tricks;
    };

}  // namespace nobridge::engine

#endif
