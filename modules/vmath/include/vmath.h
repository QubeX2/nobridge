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
    const size_t POS0_HCP = 0;
    const size_t POS1_MAJOR_LENGTH = 1;
    const size_t POS2_MINOR_LENGTH = 2;
    const size_t POS3_DIST_POINTS = 3;
    const size_t POS4_SPADES_COUNT = 4;
    const size_t POS5_HEARTS_COUNT = 5;
    const size_t POS6_DIAMONDS_COUNT = 6;
    const size_t POS7_CLUBS_COUNT = 7;
    const size_t POS8_VULNERABLE = 8;
    const size_t POS9_DEALER = 9;
    const size_t POS10_ACES = 10;
    const size_t POS11_KINGS = 11;
    const size_t POS12_QUEENS = 12;
    const size_t POS13_JACKS = 13;
    const size_t POS_SIZE = 14;

    // Pos: 0 - HCP
    const float ACE_POINTS = 4.5f;
    const float KING_POINTS = 3.5f;
    const float QUEEN_POINTS = 2.0f;
    const float JACK_POINTS = 1.0f;
    const float TEN_POINTS = 0.5f;

    // Pos: 1 - Four Card Major Suit
    const float LONG_MAJOR_SUIT = 1.0f;

    // Pos: 2 - Four Card Minor Suit
    const float LONG_MINOR_SUIT = 1.0f;

    // Pos: 3 - Dist Points

    // Pos: 4 - 7 - Suit count

    const LegendMap<std::size_t> HAND_LEGEND{
        {0, "HCP"},     {1, "Majors"}, {2, "Minors"},   {3, "Dist"},
        {4, "Spades"},  {5, "Hearts"}, {6, "Diamonds"}, {7, "Clubs"},
        {8, "Vuln"},    {9, "Dealer"}, {10, "Aces"},    {11, "Kings"},
        {12, "Queens"}, {13, "Jacks"}};

    using HandVect = mika::VecT<float, POS_SIZE>;

    UIntArray<HAND_LENGTH> toArrayFromCards(const engine::CardList& cards);
    UIntVal toIntFromCard(const engine::CardPtr& card);
    engine::CardPtr toCardFromInt(const UIntVal num);
    UIntArray<4> countSuits(const engine::CardList& cards);
    UIntArray<13> countRanks(const engine::CardList& cards);
    float calculateHCP(const engine::CardList& cards);
    float calculateDist(const engine::CardList& cards);
    HandVect toVector(const engine::HandPtr& hand);
    UIntVal rankCount(UIntArray<13> list, engine::Rank rank);

}  // namespace nobridge::vmath

#endif
