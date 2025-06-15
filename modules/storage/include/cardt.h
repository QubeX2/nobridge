#ifndef STORAGE_CARDT_H
#define STORAGE_CARDT_H

#include <cstdint>

namespace nobridge::storage {

    class CardT {
       public:
       private:
        uint8_t m_suit;
        uint8_t m_rank;
    };

}  // namespace nobridge::storage

#endif
