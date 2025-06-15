#ifndef STORAGE_HANDVEC_H
#define STORAGE_HANDVEC_H

#include <sys/wait.h>

#include <array>
#include <cstdint>
#include <utility>

namespace nobridge::storage {

    struct CardData {
        uint8_t m_suit;
        uint8_t m_rank;
    };

    class HandVec {
       public:
       private:
        uint8_t m_hcp = 0;

        uint8_t m_spade_count = 0;
        uint8_t m_heart_count = 0;
        uint8_t m_diamond_count = 0;
        uint8_t m_club_count = 0;

        // suit, rank
        std::array<CardData, 13> m_hand;
    };

}  // namespace nobridge::storage

#endif
