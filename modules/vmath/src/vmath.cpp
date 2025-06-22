#include "vmath.h"

#include <cstdint>

#include "card.h"
#include "hand.h"
#include "types.h"

namespace nobridge::vmath {
    /**
     *
     */
    uint8_t rankCount(UIntArray<13> list, engine::Rank rank) {
        return list[static_cast<uint8_t>(rank) - 2];
    }

    /**
     *
     */
    HandVect toVector(const engine::HandPtr& hand) {
        UIntArray<4> suits = countSuits(hand->cards());
        UIntArray<13> ranks = countRanks(hand->cards());

        HandVect hvect{};
        hvect.setLegend(kHandLegend);

        hvect[kPos0_Hcp] = calculateHCP(hand->cards());

        hvect[kPos1_MajorLength] =
            suits[0] >= 4 ? suits[0] * kLongMajorSuit : 0;
        hvect[kPos1_MajorLength] +=
            suits[1] >= 4 ? suits[1] * kLongMajorSuit : 0;
        hvect[kPos2_MinorLength] =
            suits[2] >= 4 ? suits[2] * kLongMinorSuit : 0;
        hvect[kPos2_MinorLength] +=
            suits[3] >= 4 ? suits[3] * kLongMinorSuit : 0;

        hvect[kPos3_DistPoints] = calculateDist(hand->cards());
        hvect[kPos4_SpadesCount] = static_cast<float>(suits[0]);
        hvect[kPos5_HeartsCount] = static_cast<float>(suits[1]);
        hvect[kPos6_DiamondsCount] = static_cast<float>(suits[2]);
        hvect[kPos7_ClubsCount] = static_cast<float>(suits[3]);
        hvect[kPos8_Vulnerable] = 0;
        hvect[kPos9_Dealer] = 0;
        hvect[kPos10_Aces] = rankCount(ranks, engine::Rank::ACE) * 2.0f;
        hvect[kPos11_Kings] = rankCount(ranks, engine::Rank::KING) * 1.0f;
        hvect[kPos12_Queens] = rankCount(ranks, engine::Rank::QUEEN) * 0.5f;
        hvect[kPos13_Jacks] = rankCount(ranks, engine::Rank::JACK) * 0.25f;

        return hvect;
    }

    /**
     *
     */
    UIntArray<4> countSuits(const engine::CardList& cards) {
        UIntArray<4> handcount{};
        for (const engine::CardPtr& card : cards) {
            handcount[static_cast<uint8_t>(card->suit()) - 1]++;
        }
        return handcount;
    }

    /**
     *
     */
    UIntArray<13> countRanks(const engine::CardList& cards) {
        UIntArray<13> rankcount{};
        for (const engine::CardPtr& card : cards) {
            rankcount[static_cast<std::size_t>(card->rank()) - 2]++;
        }
        return rankcount;
    }

    /**
     *
     */
    float calculateHCP(const engine::CardList& cards) {
        float score{};
        for (const engine::CardPtr& card : cards) {
            score += card->rank() == engine::Rank::ACE ? kAcePoints : 0;
            score += card->rank() == engine::Rank::KING ? kKingPoints : 0;
            score += card->rank() == engine::Rank::QUEEN ? kQueenPoints : 0;
            score += card->rank() == engine::Rank::JACK ? kJackPoints : 0;
            score += card->rank() == engine::Rank::TEN ? kTenPoints : 0;
        }
        return score;
    }

    /**
     *
     */
    float calculateDist(const engine::CardList& cards) {
        float score{};
        UIntArray<4> suits = countSuits(cards);
        for (uint8_t count : suits) {
            if (count <= 2) {
                score += 3 - count;
            }
        }
        return score;
    }

}  // namespace nobridge::vmath
