#include <gtest/gtest.h>

#include "adapter.h"
#include "deck.h"
#include "engine.h"
#include "parser.h"
#include "pbn.h"

using namespace nobridge;

TEST(PbnTest, HandlesPbnFiles) {
    pbn::GameList gl =
        pbn::processFile("files/RB_220702123558SistaChansen_full.pbn.txt");

    EXPECT_GE(gl.size(), 0);
}

TEST(PbnAdapter, AdapterTest) {
    pbn::GameList gamelist =
        pbn::processFile("files/RB_220702123558SistaChansen_full.pbn.txt");

    if (!gamelist.empty()) {
        pbn::TagMap tags = gamelist[0];

        if (tags.contains("Deal")) {
            engine::DealList deal = adapter::pbn::toDeal(tags["Deal"]->value);

            EXPECT_EQ(deal.size(), 4);

            engine::output::printDeal(deal);
        }
    }
}
