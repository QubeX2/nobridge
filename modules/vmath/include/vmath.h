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
    enum HandVectPos {
        HCP = 0,
        MAJOR_LENGTH,
        MINOR_LENGTH,
        DIST_POINTS,
        SPADES_COUNT,
        HEARTS_COUNT,
        DIAMONDS_COUNT,
        CLUBS_COUNT,
        VULNERABLE,
        DEALER,
        ACES,
        KINGS,
        QUEENS,
        JACKS,
        BALANCED,
        SPADES_HCP,
        HEARTS_HCP,
        DIAMONDS_HCP,
        CLUBS_HCP
    };

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

    // History of played cards 1.0f played etc
    using PlayedCardsVect = mika::VecT<float, VECT_PLAYED_CARDS_SIZE>;

    // Hand + Bidder + Partner + Current
    using AuctionVect = mika::VecT<float, VECT_HAND_SIZE + (VECT_CONTRACT_SIZE * 3)>;

    // Play Vector - Player + Dummy + Contract + PlayedCards
    using PlayVect =
        mika::VecT<float, (VECT_HAND_SIZE * 2) + VECT_CONTRACT_SIZE + VECT_PLAYED_CARDS_SIZE>;

    // Vector Creators
    HandVect toVector(const engine::HandPU& hand);
    ContractVect toContract(const engine::BidPU& bid);
    PlayedCardsVect& addPlayedCard(PlayedCardsVect& vect, const engine::CardPU& card);

    AuctionVect toAuction(const HandVect& player, const ContractVect& bidder,
                          const ContractVect& partner, const ContractVect& current);

    PlayVect toPlay(const HandVect& player, const HandVect& dummy, const ContractVect& contract,
                    const PlayedCardsVect& played);

}  // namespace nobridge::vmath

#endif
