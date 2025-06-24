#include "vmath.h"

#include <cstdint>
#include <memory>

#include "card.h"
#include "hand.h"
#include "types.h"

namespace nobridge::vmath {
    /**
     *
     */
    engine::CardPtr toCardFromInt(const UIntVal num) {
        if (num < 1 || num > 52) return nullptr;
        UIntVal znum = num - 1;
        UIntVal suit = (num / 13) + 1;
        UIntVal rank = (num % 13) + 1;
        std::cout << std::format("Num: {}, Suit: {}, Rank: {}", num, suit,
                                 rank);
        engine::CardPtr card = std::make_shared<engine::Card>(
            static_cast<engine::Suit>(suit), static_cast<engine::Rank>(rank));
        return card;
    }

    /**
     *
     */
    UIntVal toIntFromCard(const engine::CardPtr& card) {
        return (static_cast<UIntVal>(card->suit()) - 1) * HAND_LENGTH +
               static_cast<UIntVal>(card->rank()) - 1;
    }

    /**
     *
     */
    UIntVal rankCount(UIntArray<HAND_LENGTH> list, engine::Rank rank) {
        return list[static_cast<UIntVal>(rank) - 2];
    }

    /**
     *
     */
    HandVect toVector(const engine::HandPtr& hand) {
        UIntArray<4> suits = countSuits(hand->cards());
        UIntArray<13> ranks = countRanks(hand->cards());

        HandVect hvect{};
        hvect.setLegend(HAND_LEGEND);

        hvect[POS0_HCP] = calculateHCP(hand->cards());

        hvect[POS1_MAJOR_LENGTH] =
            suits[0] >= 4 ? suits[0] * LONG_MAJOR_SUIT : 0;
        hvect[POS1_MAJOR_LENGTH] +=
            suits[1] >= 4 ? suits[1] * LONG_MAJOR_SUIT : 0;
        hvect[POS2_MINOR_LENGTH] =
            suits[2] >= 4 ? suits[2] * LONG_MINOR_SUIT : 0;
        hvect[POS2_MINOR_LENGTH] +=
            suits[3] >= 4 ? suits[3] * LONG_MINOR_SUIT : 0;

        hvect[POS3_DIST_POINTS] = calculateDist(hand->cards());
        hvect[POS4_SPADES_COUNT] = static_cast<float>(suits[0]);
        hvect[POS5_HEARTS_COUNT] = static_cast<float>(suits[1]);
        hvect[POS6_DIAMONDS_COUNT] = static_cast<float>(suits[2]);
        hvect[POS7_CLUBS_COUNT] = static_cast<float>(suits[3]);
        hvect[POS8_VULNERABLE] = 0;
        hvect[POS9_DEALER] = 0;
        hvect[POS10_ACES] = rankCount(ranks, engine::Rank::ACE) * 2.0f;
        hvect[POS11_KINGS] = rankCount(ranks, engine::Rank::KING) * 1.0f;
        hvect[POS12_QUEENS] = rankCount(ranks, engine::Rank::QUEEN) * 0.5f;
        hvect[POS13_JACKS] = rankCount(ranks, engine::Rank::JACK) * 0.25f;

        return hvect;
    }

    /**
     *
     */
    UIntArray<4> countSuits(const engine::CardList& cards) {
        UIntArray<4> handcount{};
        for (const engine::CardPtr& card : cards) {
            handcount[static_cast<UIntVal>(card->suit()) - 1]++;
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
            score += card->rank() == engine::Rank::ACE ? ACE_POINTS : 0;
            score += card->rank() == engine::Rank::KING ? KING_POINTS : 0;
            score += card->rank() == engine::Rank::QUEEN ? QUEEN_POINTS : 0;
            score += card->rank() == engine::Rank::JACK ? JACK_POINTS : 0;
            score += card->rank() == engine::Rank::TEN ? TEN_POINTS : 0;
        }
        return score;
    }

    /**
     *
     */
    float calculateDist(const engine::CardList& cards) {
        float score{};
        UIntArray<4> suits = countSuits(cards);
        for (UIntVal count : suits) {
            if (count <= 2) {
                score += 3 - count;
            }
        }
        return score;
    }

}  // namespace nobridge::vmath
