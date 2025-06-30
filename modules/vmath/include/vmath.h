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

    const size_t VECT_HAND_SIZE = 19;
    const size_t VECT_CONTRACT_SIZE = 6;
    const size_t VECT_PLAYED_CARDS_SIZE = 52;

    const float RISK_SCALAR_VOID = 0.0f;
    const float RISK_SCALAR_X = 1.0f;
    const float RISK_SCALAR_XX = 2.0f;

    const float TRUE_SCALAR = 1.0f;
    const float FALSE_SCALAR = 0.0f;

    const LegendM<std::size_t> HAND_LEGEND{
        {0, "HCP"},    {1, "Majors"},   {2, "Minors"},  {3, "Dist"},   {4, "Spades"},
        {5, "Hearts"}, {6, "Diamonds"}, {7, "Clubs"},   {8, "Vuln"},   {9, "Dealer"},
        {10, "Aces"},  {11, "Kings"},   {12, "Queens"}, {13, "Jacks"}, {14, "Balanced"},
        {15, "S-HCP"}, {16, "H-HCP"},   {17, "D-HCP"},  {18, "C-HCP"}};

    using HandVect = mika::VecT<float, VECT_HAND_SIZE>;

    // [S, H, D, C, NT, R] 0 - 7; (R = Risk, X = 1.0f, XX = 2.0f)
    using ContractVect = mika::VecT<float, VECT_CONTRACT_SIZE>;

    // Bidder + Partner + Current
    using AuctionVect = mika::VecT<float, VECT_CONTRACT_SIZE * 3>;

    // History of played cards 1.0f played etc
    using PlayedCardsVect = mika::VecT<float, VECT_PLAYED_CARDS_SIZE>;

    // Play Vector
    using PlayVect =
        mika::VecT<float, (VECT_HAND_SIZE * 2) + VECT_CONTRACT_SIZE + VECT_PLAYED_CARDS_SIZE>;

    // Vector Creators
    HandVect toVector(const engine::HandPU& hand);
    ContractVect toContract(const engine::BidPU& bid);
    PlayedCardsVect& addPlayedCard(PlayedCardsVect& vect, const engine::CardPU& card);

    AuctionVect toAuction(const ContractVect& bidder, const ContractVect& partner,
                          const ContractVect& current);
    PlayVect toPlay(const HandVect& player, const HandVect& dummy, const ContractVect& contract,
                    const PlayedCardsVect& played);

}  // namespace nobridge::vmath

#endif
