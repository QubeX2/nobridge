#include <gtest/gtest.h>

#include <memory>

#include "deck.h"
#include "engine.h"

TEST(DeckTest, HandlesShuffling) {
    nobridge::engine::DeckPtr deck = std::make_shared<nobridge::engine::Deck>();
    deck->shuffle();
    ASSERT_NE(deck->at(0), nullptr) << "nullptr at(0)";
    EXPECT_GT(static_cast<int>(deck->at(0)->suit()), 0);
    EXPECT_GT(static_cast<int>(deck->at(0)->rank()), 0);

    nobridge::engine::output::printDeck(deck);
}
