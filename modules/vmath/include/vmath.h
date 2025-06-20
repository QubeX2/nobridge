#include "card.h"
#include "vect.h"

namespace nobridge::vmath {
    const size_t kPosHcp = 0;
    const size_t kPosMajorLength = 1;
    const size_t kPosMinorLength = 2;
    const size_t kPosDistPoints = 3;
    const size_t kPosSpadesCount = 4;
    const size_t kPosHeartsCount = 5;
    const size_t kPosDiamondsCount = 6;
    const size_t kPosClubsCount = 7;

    // Pos: 0 - HCP
    const float kAcePoints = 4.5f;
    const float kKingPoints = 3.5f;
    const float kQueenPoints = 2.0f;
    const float kJackPoints = 1.0f;
    const float kTenPoints = 0.5f;

    // Pos: 1 - Four Card Major Suit
    const float kFourCardMajorSuit = 1.0f;
    const float kFiveCardMajorSuit = 2.0f;

    // Pos: 1 - Long Major Suit
    const float kSixCardMajorSuit = 1.0f;
    const float kSevenCardMajorSuit = 2.0f;
    const float kEightCardMajorSuit = 3.0f;
    const float kLongCardMajorSuit = 4.0f;

    // Pos: 2 - Four Card Minor Suit
    const float kFourCardMinorSuit = 1.0f;
    const float kFiveCardMinorSuit = 2.0f;

    // Pos: 2 - Long Minor Suit
    const float kSixCardMinorSuit = 1.0f;
    const float kSevenCardMinorSuit = 2.0f;
    const float kEightCardMinorSuit = 3.0f;
    const float kLongCardMinorSuit = 4.0f;

    // Pos: 3 - Dist Points
    const float kDistDoubleton = 1.0f;
    const float kDistSingleton = 2.0f;
    const float kDistVoid = 3.0f;

    // Pos: 4 - 7 - Suit count

    using UIntArray4 = std::array<uint8_t, 4>;
    using HandVecT = mika::VecT<float, 20>;

    UIntArray4 countSuits(const engine::CardList& cards);
    float calculateHCP(const engine::CardList& cards);
    HandVecT toVector(const engine::CardList cards);

}  // namespace nobridge::vmath
