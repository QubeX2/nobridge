#include "vmath.h"

#include "card.h"

namespace nobridge::vmath {
    /**
     *
     */
    HandVecT toVector(const engine::CardList cards) {
        UIntArray4 suits = countSuits(cards);
        HandVecT hand{};

        hand[kPosHcp] = calculateHCP(cards);
        hand[kPosMajorLength] = suits[0] >= 4 ? suits[0] * kLongMajorSuit : 0;
        hand[kPosMajorLength] += suits[1] >= 4 ? suits[1] * kLongMajorSuit : 0;
        hand[kPosDistPoints] = calculateDist(cards);
        hand[kPosSpadesCount] = static_cast<float>(suits[0]);
        hand[kPosHeartsCount] = static_cast<float>(suits[1]);
        hand[kPosDiamondsCount] = static_cast<float>(suits[2]);
        hand[kPosClubsCount] = static_cast<float>(suits[3]);

        return hand;
    }

    /**
     *
     */
    UIntArray4 countSuits(const engine::CardList& cards) {
        UIntArray4 handcount{};
        for (const engine::CardPtr& card : cards) {
            handcount[static_cast<uint8_t>(card->suit()) - 1]++;
        }
        for (auto n : handcount) {
            std::println("N: {}", n);
        }
        return handcount;
    }

    /**
     *
     */
    UIntArray13 countRanks(const engine::CardList& cards) {
        UIntArray13 rankcount{};
        for (const engine::CardPtr& card : cards) {
            rankcount[static_cast<size_t>(card->rank()) - 2]++;
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
        UIntArray13 ranks = countRanks(cards);
        for (auto rank : ranks) {
            if (rank <= 2) {
                score += 3 - rank;
            }
        }
    }

}  // namespace nobridge::vmath
