#include <gtest/gtest.h>

#include <memory>

#include "deck.h"
#include "engine.h"

using namespace nobridge;

TEST(DeckTest, HandlesShuffling) {
    engine::DeckPtr deck = std::make_shared<engine::Deck>();
    deck->shuffle();
    ASSERT_NE(deck->at(0), nullptr) << "nullptr at(0)";
    EXPECT_GT(static_cast<int>(deck->at(0)->suit()), 0);
    EXPECT_GT(static_cast<int>(deck->at(0)->rank()), 0);

    // engine::output::printDeck(deck);
}
