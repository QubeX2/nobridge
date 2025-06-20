#ifndef ADAPTER_ADAPTER_H
#define ADAPTER_ADAPTER_H

#include <sys/wait.h>

#include "card.h"
#include "deck.h"
#include "storage.h"
#include "vect.h"

namespace nobridge::adapter {

    namespace pbn {
        // spades, hearts, diamonds, clubs
        engine::DealList toDeal(const std::string& dealstr);

    }  // namespace pbn

}  // namespace nobridge::adapter
#endif
