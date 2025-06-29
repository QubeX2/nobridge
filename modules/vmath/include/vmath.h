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
    const size_t POS10_ACES = 10;  // suit count
    const size_t POS11_KINGS = 11;
    const size_t POS12_QUEENS = 12;
    const size_t POS13_JACKS = 13;
    const size_t POS14_BALANCED = 14;
    const size_t POS15_SPADES_HCP = 15;
    const size_t POS16_HEARTS_HCP = 16;
    const size_t POS17_DIAMONDS_HCP = 17;
    const size_t POS18_CLUBS_HCP = 18;
    const size_t POS_SIZE = 19;

    const LegendM<std::size_t> HAND_LEGEND{
        {0, "HCP"},    {1, "Majors"},   {2, "Minors"},  {3, "Dist"},   {4, "Spades"},
        {5, "Hearts"}, {6, "Diamonds"}, {7, "Clubs"},   {8, "Vuln"},   {9, "Dealer"},
        {10, "Aces"},  {11, "Kings"},   {12, "Queens"}, {13, "Jacks"}, {14, "Balanced"},
        {15, "S-HCP"}, {16, "H-HCP"},   {17, "D-HCP"},  {18, "C-HCP"}};

    using HandVect = mika::VecT<float, POS_SIZE>;

    // Get a Hand Vector from a HandP
    HandVect toVector(const engine::HandPU& hand);

}  // namespace nobridge::vmath

#endif
