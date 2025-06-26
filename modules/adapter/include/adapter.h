#ifndef ADAPTER_ADAPTER_H
#define ADAPTER_ADAPTER_H

#include <sys/wait.h>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "parser.h"
#include "types.h"

namespace nobridge::adapter {
    engine::CardPtr toCard(const std::string& string);
    engine::DealList toDeal(const std::string& dealstr);
    std::string toHandstr(const engine::CardList cards);
    engine::GamePtr toGame(nobridge::pbn::TagMap tags);
}  // namespace nobridge::adapter
#endif
