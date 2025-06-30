#include "vmath.h"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>

#include "bid.h"
#include "card.h"
#include "hand.h"
#include "helpers.h"
#include "types.h"

namespace nobridge::vmath {
    PlayedCardsVect& addPlayedCard(PlayedCardsVect& vect, const engine::CardPU& card) {
        UIntV ix = engine::Hand::toInt(card);
        vect[ix - 1] = TRUE_SCALAR;
        return vect;
    }

    /**
     * From a Bid pointer with properties level(), denomination() and risk()
     * to a float ContractVect [S, H, D, C, NT, R], R is for risk Void = 0.0f, X = 1.0f, XX = 2.0f
     */
    ContractVect toContract(const engine::BidPU& bid) {
        ContractVect contractVect{};

        float level = static_cast<float>(bid->level());

        switch (bid->denomination()) {
            case engine::Denomination::SPADES:
                contractVect[0] = level;
                break;
            case engine::Denomination::HEARTS:
                contractVect[1] = level;
                break;
            case engine::Denomination::DIAMONDS:
                contractVect[2] = level;
                break;
            case engine::Denomination::CLUBS:
                contractVect[3] = level;
                break;
            case engine::Denomination::NOTRUMP:
                contractVect[4] = level;
                break;
            default:
                break;
        }

        // Map the bid's risk level to the last index of the contractVect.
        switch (bid->risk()) {
            case engine::Risk::VOID:
                contractVect[5] = 0.0f;  // As per comment: Void = 0.0f
                break;
            case engine::Risk::DOUBLED:
                contractVect[5] = 1.0f;  // As per comment: X = 1.0f
                break;
            case engine::Risk::REDOUBLED:
                contractVect[5] = 2.0f;  // As per comment: XX = 2.0f
                break;
            default:
                break;
        }

        return contractVect;
    }

    /**
     *
     */
    HandVect toVector(const engine::HandPU& hand) {
        UIntA<4> suits = hand->suits();
        UIntA<13> ranks = hand->ranks();

        HandVect hvect{};
        hvect.setLegend(HAND_LEGEND);

        hvect[HandVectPos::HCP] = hand->HCP();

        hvect[HandVectPos::MAJOR_LENGTH] = suits[0] >= 4 ? suits[0] * LONG_MAJOR_SUIT : 0;
        hvect[HandVectPos::MAJOR_LENGTH] += suits[1] >= 4 ? suits[1] * LONG_MAJOR_SUIT : 0;
        hvect[HandVectPos::MINOR_LENGTH] = suits[2] >= 4 ? suits[2] * LONG_MINOR_SUIT : 0;
        hvect[HandVectPos::MINOR_LENGTH] += suits[3] >= 4 ? suits[3] * LONG_MINOR_SUIT : 0;

        hvect[HandVectPos::DIST_POINTS] = hand->distribution();
        hvect[HandVectPos::SPADES_COUNT] = static_cast<float>(suits[0]);
        hvect[HandVectPos::HEARTS_COUNT] = static_cast<float>(suits[1]);
        hvect[HandVectPos::DIAMONDS_COUNT] = static_cast<float>(suits[2]);
        hvect[HandVectPos::CLUBS_COUNT] = static_cast<float>(suits[3]);
        hvect[HandVectPos::VULNERABLE] = 0;
        hvect[HandVectPos::DEALER] = 0;
        hvect[HandVectPos::ACES] = engine::Hand::rankCount(ranks, engine::Rank::ACE) * 2.0f;
        hvect[HandVectPos::KINGS] = engine::Hand::rankCount(ranks, engine::Rank::KING) * 1.0f;
        hvect[HandVectPos::QUEENS] = engine::Hand::rankCount(ranks, engine::Rank::QUEEN) * 0.5f;
        hvect[HandVectPos::JACKS] = engine::Hand::rankCount(ranks, engine::Rank::JACK) * 0.25f;
        hvect[HandVectPos::BALANCED] = hand->balanced();
        FloatA shcp = hand->suitHCP();
        hvect[HandVectPos::SPADES_HCP] = shcp[0];
        hvect[HandVectPos::HEARTS_HCP] = shcp[1];
        hvect[HandVectPos::DIAMONDS_HCP] = shcp[2];
        hvect[HandVectPos::CLUBS_HCP] = shcp[3];
        return hvect;
    }

}  // namespace nobridge::vmath
