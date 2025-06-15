#ifndef STORAGE_PLAYT_H
#define STORAGE_PLAYT_H

#include <array>

#include "cardt.h"

namespace nobridge::storage {

    class PlayT {
       public:
       private:
        std::array<std::array<CardT, 4>, 13> m_tricks;
    };

}  // namespace nobridge::storage

#endif
