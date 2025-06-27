#ifndef ENGINE_HELPERS_H
#define ENGINE_HELPERS_H

#include "types.h"

namespace nobridge::engine {
    // Rotate Direction

    // Get Int Hand array from a list of Card's
    UIntA<HAND_LENGTH> toArrayFromCards(const CardL& cards);

    // Get an Int from a Card
    UIntV toIntFromCard(const CardP& card);

    // Get a CardP from an integer
    CardP toCardFromInt(const UIntV num);

    // Get an array of counted suits [S,H,D,C];
    UIntA<4> countSuits(const CardL& cards);

    // Get an array of counted ranks [2,3,4,5,6,7,8,9,T,J,Q,K,A];
    UIntA<13> countRanks(const CardL& cards);

    // Calculate HCP from a list of Card's
    float calculateHCP(const CardL& cards);

    // Calculate Distribution from a list of Card's
    float calculateDist(const CardL& cards);

    // Count a specific rank from an array of counted ranks
    UIntV rankCount(UIntA<13> list, Rank rank);

}  // namespace nobridge::engine

#endif
