#include <gtest/gtest.h>

#include <memory>

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "helpers.h"
#include "types.h"

using namespace nobridge;

TEST(DeckTest, HandlesShuffling) {
    engine::DeckPU deck = std::make_unique<engine::Deck>();
    deck->shuffle();
    ASSERT_NE(deck->at(0), nullptr) << "nullptr at(0)";
    EXPECT_GT(static_cast<int>(deck->at(0)->suit()), 0);
    EXPECT_GT(static_cast<int>(deck->at(0)->rank()), 0);

    // engine::output::printDeck(deck);
}

TEST(CardTest, CardToInteger) {
    engine::CardPU card = std::make_unique<engine::Card>(engine::Suit::CLUBS, engine::Rank::ACE);

    EXPECT_EQ(engine::Hand::toInt(card), 52);

    card->setSuitAndRank(engine::Suit::SPADES, engine::Rank::ACE);
    EXPECT_EQ(engine::Hand::toInt(card), 13);

    card->setSuitAndRank(engine::Suit::DIAMONDS, engine::Rank::TWO);
    EXPECT_EQ(engine::Hand::toInt(card), 27);

    engine::CardPU icard = engine::Hand::toCard(40);
    if (icard != nullptr) {
        EXPECT_EQ(icard->suit(), engine::Suit::CLUBS);
        EXPECT_EQ(icard->rank(), engine::Rank::TWO);
    }
}
