#ifndef ADAPTER_ADAPTER_H
#define ADAPTER_ADAPTER_H

#include <sys/wait.h>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "parser.h"
#include "types.h"

namespace nobridge::adapter {
    engine::CardP toCard(const std::string& string);
    engine::DealL toDeal(const std::string& dealstr);
    std::string toHandstr(const engine::CardL cards);
    engine::GamePU toGame(nobridge::pbn::TagM tags);
}  // namespace nobridge::adapter
#endif
