#include <gtest/gtest.h>

#include <filesystem>
#include <memory>

#include "adapter.h"
#include "deck.h"
#include "engine.h"
#include "game.h"
#include "hand.h"
#include "parser.h"
#include "pbn.h"
#include "storage.h"
#include "vect.h"
#include "vmath.h"

using namespace nobridge;

class StorageTest : public testing::Test {
   public:
    StorageTest() {
        m_gl =
            pbn::processFile("files/RB_220702123558SistaChansen_full.pbn.txt");
    }
    pbn::GameList m_gl;
};

TEST(VectorTest, HandlesVectorMath) {
    mika::VecT<float, 5> vec5a{1.0, 0.0, 0.0, 0.0, 0.0};
    mika::VecT<float, 5> vec5b{0.0, 1.0, 0.0, 0.0, 0.0};

    // std::cout << std::format("Radian: {}, Degree: {}\n", vec5a.angle(vec5b),
    //                         vec5a.angleDeg(vec5b));

    EXPECT_EQ(vec5a.length(), 1);
    EXPECT_EQ(vec5a.angleDeg(vec5b), 90);

    // std::cout << vec5a
    // std::cout << vec5b
}

TEST_F(StorageTest, Conversion) {
    if (!m_gl.empty()) {
        pbn::TagMap tags = m_gl[0];

        if (tags.contains("Deal")) {
            engine::DealList deal = adapter::toDeal(tags["Deal"]->value);
            if (!deal.empty()) {
                for (auto cards : deal) {
                    engine::HandPtr hand =
                        std::make_shared<engine::Hand>(cards, false, false);
                    vmath::HandVect vec = vmath::toVector(hand);
                    EXPECT_GE(vec[0], 0);
                    // engine::output::printCards(cards);
                    // std::cout << vec
                }
            }
        }
    }
}

TEST_F(StorageTest, CreateHandRec) {
    if (!m_gl.empty()) {
        pbn::TagMap tags = m_gl[0];

        if (tags.contains("Deal")) {
            engine::DealList deal = adapter::toDeal(tags["Deal"]->value);
            auto hstr = adapter::toHandstr(deal[0]);
            auto hand = std::make_shared<engine::Hand>(deal[0], false, false);
            auto hvec = vmath::toVector(hand);
            auto hr = storage::createHandRec<float, 14>(
                storage::uniqueId(), hstr, hvec.data(), hvec.length(),
                hvec.angle());
            EXPECT_GE(hr.id, 0);

            // std::cout << hr
        }
    }
}

TEST(WriteAndReadVectorToFile, Storage) {
    vmath::HandVect vecw{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
                         0.8, 0.9, 1.0, 1.1, 1.2, 1.2, 1.3};

    storage::write("./vector.bin", vecw.asBytes(), vecw.byteSize());
    EXPECT_TRUE(std::filesystem::exists("./vector.bin"));

    vmath::HandVect vecr;
    storage::read("./vector.bin", vecr.asBytes(), vecr.byteSize());
    EXPECT_EQ(vecr[1], 0.2f);
}

TEST_F(StorageTest, PbnToEngineGame) {
    if (!m_gl.empty()) {
        pbn::TagMap tags = m_gl[0];
        engine::GamePtr game = adapter::toGame(tags);
        std::cout << game << "\n";
    }
}
