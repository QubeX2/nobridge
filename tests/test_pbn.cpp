#include <gtest/gtest.h>

#include "adapter.h"
#include "deck.h"
#include "engine.h"
#include "parser.h"
#include "pbn.h"

TEST(PbnTest, HandlesPbnFiles) {
    nobridge::pbn::GameList gl = nobridge::pbn::processFile(
        "files/RB_220702123558SistaChansen_full.pbn.txt");

    EXPECT_GE(gl.size(), 0);
}

TEST(PbnAdapter, AdapterTest) {
    nobridge::pbn::GameList gamelist = nobridge::pbn::processFile(
        "files/RB_220702123558SistaChansen_full.pbn.txt");

    if (!gamelist.empty()) {
        nobridge::pbn::TagMap tags = gamelist[0];

        if (tags.contains("Deal")) {
            nobridge::engine::DealList deal =
                nobridge::adapter::pbn::toDeal(tags["Deal"]->value);

            EXPECT_EQ(deal.size(), 4);

            nobridge::engine::output::printDeal(deal);
        }
    }
}
