#ifndef STORAGE_HANDT_H
#define STORAGE_HANDT_H

#include <sys/wait.h>

#include <array>
#include <cstdint>
#include <utility>

#include "cardt.h"

namespace nobridge::storage {

    class HandT {
       public:
       private:
        uint8_t m_hcp = 0;

        uint8_t m_spade_count = 0;
        uint8_t m_heart_count = 0;
        uint8_t m_diamond_count = 0;
        uint8_t m_club_count = 0;
        uint8_t m_longest_suit = 0;
        bool m_is_balanced = false;
        bool m_has_4_card_major = 0;

        // suit, rank
        std::array<CardT, 13> m_hand;
    };

}  // namespace nobridge::storage

#endif
