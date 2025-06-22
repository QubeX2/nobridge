#ifndef VMATH_VMATH_H
#define VMATH_VMATH_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <unordered_map>

#include "card.h"
#include "hand.h"
#include "types.h"
#include "vect.h"

namespace nobridge::vmath {
    const size_t kPos0_Hcp = 0;
    const size_t kPos1_MajorLength = 1;
    const size_t kPos2_MinorLength = 2;
    const size_t kPos3_DistPoints = 3;
    const size_t kPos4_SpadesCount = 4;
    const size_t kPos5_HeartsCount = 5;
    const size_t kPos6_DiamondsCount = 6;
    const size_t kPos7_ClubsCount = 7;
    const size_t kPos8_Vulnerable = 8;
    const size_t kPos9_Dealer = 9;
    const size_t kPos10_Aces = 10;
    const size_t kPos11_Kings = 11;
    const size_t kPos12_Queens = 12;
    const size_t kPos13_Jacks = 13;
    const size_t kPosSize = 14;

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

    const LegendMap<std::size_t> kHandLegend{
        {0, "HCP"},     {1, "Majors"}, {2, "Minors"},   {3, "Dist"},
        {4, "Spades"},  {5, "Hearts"}, {6, "Diamonds"}, {7, "Clubs"},
        {8, "Vuln"},    {9, "Dealer"}, {10, "Aces"},    {11, "Kings"},
        {12, "Queens"}, {13, "Jacks"}};

    using HandVect = mika::VecT<float, kPosSize>;

    UIntArray<4> countSuits(const engine::CardList& cards);
    UIntArray<13> countRanks(const engine::CardList& cards);
    float calculateHCP(const engine::CardList& cards);
    float calculateDist(const engine::CardList& caads);
    HandVect toVector(const engine::HandPtr& hand);
    uint8_t rankCount(UIntArray<13> list, engine::Rank rank);

}  // namespace nobridge::vmath

#endif
