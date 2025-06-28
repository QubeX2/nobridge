#ifndef ADAPTER_ADAPTER_H
#define ADAPTER_ADAPTER_H

#include <sys/wait.h>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "parser.h"
#include "types.h"

namespace nobridge::adapter {
    engine::CardPU toCard(const std::string& string);
    engine::DeclS toDecl(const std::string& bid);
    engine::DealL toDeal(const std::string& dealstr);
    engine::GamePU toGame(const nobridge::pbn::TagM& tags);
    engine::Direction toDirection(const std::string& ch);
    engine::Denomination toDenomination(const std::string& ch);

    std::string toHandString(const engine::CardL cards);
}  // namespace nobridge::adapter
#endif
