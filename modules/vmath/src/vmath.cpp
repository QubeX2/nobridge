#include "vmath.h"

#include "card.h"

namespace nobridge::vmath {
    /**
     *
     */
    HandVecT toVector(const engine::CardList cards) {
        UIntArray4 suits = countSuits(cards);
        HandVecT hand{};

        hand[kPosSpadesCount] = suits[0];
        hand[kPosHeartsCount] = suits[1];
        hand[kPosDiamondsCount] = suits[2];
        hand[kPosClubsCount] = suits[3];

        return hand;
    }

    /**
     *
     */
    UIntArray4 countSuits(const engine::CardList& cards) {
        UIntArray4 handcount{0, 0, 0, 0};
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
    float calculateHCP(const engine::CardList& cards) {
        float score;
        for (const engine::CardPtr& card : cards) {
            score += card->rank() == engine::Rank::ACE ? kAcePoints : 0;
            score += card->rank() == engine::Rank::KING ? kKingPoints : 0;
            score += card->rank() == engine::Rank::QUEEN ? kQueenPoints : 0;
            score += card->rank() == engine::Rank::JACK ? kJackPoints : 0;
            score += card->rank() == engine::Rank::TEN ? kTenPoints : 0;
        }
        return score;
    }

}  // namespace nobridge::vmath
