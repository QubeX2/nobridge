#include <gtest/gtest.h>

#include "deck.h"

TEST(DeckTest, HandlesShuffling) {
    nobridge::engine::Deck deck;
    deck.shuffle();
    ASSERT_NE(deck.at(0), nullptr) << "nullptr at(0)";
    EXPECT_GT(static_cast<int>(deck.at(0)->suit()), 0);
    EXPECT_GT(static_cast<int>(deck.at(0)->rank()), 0);
}
