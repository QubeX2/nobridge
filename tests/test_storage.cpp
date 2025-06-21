#include <gtest/gtest.h>

#include <memory>

#include "adapter.h"
#include "deck.h"
#include "engine.h"
#include "hand.h"
#include "parser.h"
#include "pbn.h"
#include "vect.h"
#include "vmath.h"

using namespace nobridge;

TEST(VectorTest, HandlesVectorMath) {
    mika::VecT<float, 5> vec5a{1.0, 0.0, 0.0, 0.0, 0.0};
    mika::VecT<float, 5> vec5b{0.0, 1.0, 0.0, 0.0, 0.0};

    // std::cout << std::format("Radian: {}, Degree: {}\n", vec5a.angle(vec5b),
    //                         vec5a.angleDeg(vec5b));

    EXPECT_EQ(vec5a.length(), 1);
    EXPECT_EQ(vec5a.angleDeg(vec5b), 90);

    // std::cout << vec5a << std::endl;
    // std::cout << vec5b << std::endl;
}

TEST(HandToVector, Conversion) {
    pbn::GameList gamelist =
        pbn::processFile("files/RB_220702123558SistaChansen_full.pbn.txt");

    if (!gamelist.empty()) {
        pbn::TagMap tags = gamelist[0];

        if (tags.contains("Deal")) {
            engine::DealList deal = adapter::pbn::toDeal(tags["Deal"]->value);
            if (!deal.empty()) {
                for (auto cards : deal) {
                    engine::HandPtr hand =
                        std::make_shared<engine::Hand>(cards, false, false);
                    vmath::HandVecT vec = vmath::toVector(hand);
                    engine::output::printCards(cards);
                    std::cout << vec << std::endl;
                }
            }
        }
    }
}
