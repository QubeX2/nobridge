#include "vmath.h"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>

#include "card.h"
#include "hand.h"
#include "helpers.h"
#include "types.h"

namespace nobridge::vmath {
    /**
     *
     */
    HandVect toVector(const engine::HandPU& hand) {
        UIntA<4> suits = hand->suits();
        UIntA<13> ranks = hand->ranks();

        HandVect hvect{};
        hvect.setLegend(HAND_LEGEND);

        hvect[POS0_HCP] = hand->HCP();

        hvect[POS1_MAJOR_LENGTH] = suits[0] >= 4 ? suits[0] * LONG_MAJOR_SUIT : 0;
        hvect[POS1_MAJOR_LENGTH] += suits[1] >= 4 ? suits[1] * LONG_MAJOR_SUIT : 0;
        hvect[POS2_MINOR_LENGTH] = suits[2] >= 4 ? suits[2] * LONG_MINOR_SUIT : 0;
        hvect[POS2_MINOR_LENGTH] += suits[3] >= 4 ? suits[3] * LONG_MINOR_SUIT : 0;

        hvect[POS3_DIST_POINTS] = hand->distribution();
        hvect[POS4_SPADES_COUNT] = static_cast<float>(suits[0]);
        hvect[POS5_HEARTS_COUNT] = static_cast<float>(suits[1]);
        hvect[POS6_DIAMONDS_COUNT] = static_cast<float>(suits[2]);
        hvect[POS7_CLUBS_COUNT] = static_cast<float>(suits[3]);
        hvect[POS8_VULNERABLE] = 0;
        hvect[POS9_DEALER] = 0;
        hvect[POS10_ACES] = engine::Hand::rankCount(ranks, engine::Rank::ACE) * 2.0f;
        hvect[POS11_KINGS] = engine::Hand::rankCount(ranks, engine::Rank::KING) * 1.0f;
        hvect[POS12_QUEENS] = engine::Hand::rankCount(ranks, engine::Rank::QUEEN) * 0.5f;
        hvect[POS13_JACKS] = engine::Hand::rankCount(ranks, engine::Rank::JACK) * 0.25f;
        hvect[POS14_BALANCED] = hand->balanced();
        FloatA shcp = hand->suitHCP();
        hvect[POS15_SPADES_HCP] = shcp[0];
        hvect[POS16_HEARTS_HCP] = shcp[1];
        hvect[POS17_DIAMONDS_HCP] = shcp[2];
        hvect[POS18_CLUBS_HCP] = shcp[3];
        return hvect;
    }

}  // namespace nobridge::vmath
