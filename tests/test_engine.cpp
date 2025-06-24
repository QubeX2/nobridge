#include <gtest/gtest.h>

#include <memory>

#include "card.h"
#include "deck.h"
#include "types.h"
#include "vmath.h"

using namespace nobridge;

TEST(DeckTest, HandlesShuffling) {
    engine::DeckPtr deck = std::make_shared<engine::Deck>();
    deck->shuffle();
    ASSERT_NE(deck->at(0), nullptr) << "nullptr at(0)";
    EXPECT_GT(static_cast<int>(deck->at(0)->suit()), 0);
    EXPECT_GT(static_cast<int>(deck->at(0)->rank()), 0);

    // engine::output::printDeck(deck);
}

TEST(CardTest, CardToInteger) {
    engine::CardPtr card =
        std::make_shared<engine::Card>(engine::Suit::CLUBS, engine::Rank::ACE);

    EXPECT_EQ(vmath::toIntFromCard(card), 52);

    card->setSuitAndRank(engine::Suit::SPADES, engine::Rank::ACE);
    EXPECT_EQ(vmath::toIntFromCard(card), 13);

    card->setSuitAndRank(engine::Suit::DIAMONDS, engine::Rank::TWO);
    EXPECT_EQ(vmath::toIntFromCard(card), 27);

    engine::CardPtr icard = vmath::toCardFromInt(40);
    EXPECT_EQ(icard->suit(), engine::Suit::CLUBS);
    EXPECT_EQ(icard->rank(), engine::Rank::TWO);
}
