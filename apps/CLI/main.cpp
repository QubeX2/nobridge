#include <cstdint>
#include <format>
#include <iostream>
#include <print>

#include "bridgeengine.h"
#include "card.h"
#include "deck.h"

using namespace nobridge::engine;

int main() {
    Deck deck;
    deck.print();

    return 0;
}
