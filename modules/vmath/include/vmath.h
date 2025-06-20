#include <cstdint>
#include <unordered_map>

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
    const float kLongMajorSuit = 1.0f;

    // Pos: 2 - Four Card Minor Suit
    const float kLongMinorSuit = 1.0f;

    // Pos: 3 - Dist Points

    // Pos: 4 - 7 - Suit count

    using UIntArray4 = std::array<uint8_t, 4>;
    using UIntArray13 = std::array<uint8_t, 13>;
    using HandVecT = mika::VecT<float, 20>;

    UIntArray4 countSuits(const engine::CardList& cards);
    UIntArray13 countRanks(const engine::CardList& cards);
    float calculateHCP(const engine::CardList& cards);
    float calculateDist(const engine::CardList& caads);
    HandVecT toVector(const engine::CardList cards);

}  // namespace nobridge::vmath
