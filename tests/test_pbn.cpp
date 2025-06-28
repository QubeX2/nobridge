#include <gtest/gtest.h>

#include <memory>

#include "adapter.h"
#include "deck.h"
#include "engine.h"
#include "gamerec.h"
#include "parser.h"
#include "pbn.h"
#include "storage.h"
#include "types.h"
#include "vmath.h"

using namespace nobridge;

class PbnTest : public testing::Test {
   public:
    PbnTest() { m_gl = pbn::processFile("files/RB_220702123558SistaChansen_full.pbn.txt"); }
    pbn::GameL m_gl;
};

TEST_F(PbnTest, PbnToEngineGame) {
    if (!m_gl.empty()) {
        const pbn::TagM& tags = m_gl[0];
        engine::GamePU game = adapter::toGame(tags);
        std::cout << game << "\n";
    }
}

TEST(AdaperTest, StringToCard) {
    engine::CardPU card = adapter::toCard("H2");
    EXPECT_EQ(card->suit(), engine::Suit::HEARTS);
    EXPECT_EQ(card->rank(), engine::Rank::TWO);
}

TEST_F(PbnTest, HandlesPbnFiles) { EXPECT_GE(m_gl.size(), 0); }

TEST_F(PbnTest, AdapterTest) {
    if (!m_gl.empty()) {
        const pbn::TagM& tags = m_gl[0];

        if (tags.contains("Deal")) {
            engine::DealL deal = adapter::toDeal(tags.at("Deal")->value);

            EXPECT_EQ(deal.size(), 4);

            // engine::output::printDeal(deal);
        }
    }
}
