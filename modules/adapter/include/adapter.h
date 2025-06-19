#ifndef ADAPTER_ADAPTER_H
#define ADAPTER_ADAPTER_H

#include "card.h"
#include "deck.h"
#include "vect.h"

namespace nobridge::adapter {

    namespace pbn {
        // spades, hearts, diamonds, clubs
        engine::DealList toDeal(const std::string& dealstr);

    }  // namespace pbn

    namespace storage {
        using HandVecT = mika::VecT<float, 20>;

        HandVecT toVector(const engine::CardList cards);
    }  // namespace storage

}  // namespace nobridge::adapter
#endif
