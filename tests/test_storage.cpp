#include <gtest/gtest.h>

#include <filesystem>
#include <memory>

#include "adapter.h"
#include "deck.h"
#include "engine.h"
#include "hand.h"
#include "parser.h"
#include "pbn.h"
#include "storage.h"
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
                    EXPECT_GE(vec[0], 0);
                    // engine::output::printCards(cards);
                    // std::cout << vec << std::endl;
                }
            }
        }
    }
}

TEST(WriteAndReadVectorToFile, Storage) {
    vmath::HandVecT vecw{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
                         0.8, 0.9, 1.0, 1.1, 1.2, 1.2, 1.3};

    storage::write("./vector.bin", vecw.asBytes(), vecw.byteSize());
    EXPECT_TRUE(std::filesystem::exists("./vector.bin"));

    vmath::HandVecT vecr;
    storage::read("./vector.bin", vecr.asBytes(), vecr.byteSize());
    EXPECT_EQ(vecr[1], 0.2f);
}
