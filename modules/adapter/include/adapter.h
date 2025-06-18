#ifndef ADAPTER_ADAPTER_H
#define ADAPTER_ADAPTER_H

#include "deck.h"

namespace nobridge::adapter::pbn {

    // spades, hearts, diamonds, clubs
    engine::DealList toDeal(const std::string& dealstr);

}  // namespace nobridge::adapter::pbn

#endif
