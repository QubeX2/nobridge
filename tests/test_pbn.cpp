#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>

#include "parser.h"
#include "reader.h"

TEST(ReaderTest, HandlesReader) {
    nobridge::pbn::Reader reader(
        "files/RB_220702123558SistaChansen_full.pbn.txt");

    EXPECT_TRUE(reader.ok()) << "ERROR: reader.ok() is false";
    EXPECT_FALSE(reader.eof()) << "ERROR: reader.eof() is true";
    EXPECT_TRUE(reader.nextLine().length() > 0)
        << "ERROR: reader.nextLine().length() is 0";

    reader.close();
}

TEST(ParserTest, HandlesParser) {
    nobridge::pbn::Reader reader(
        "files/RB_220702123558SistaChansen_full.pbn.txt");

    nobridge::pbn::Parser parser(reader);
    parser.run();
}

TEST(PbnTest, HandlesPbnData) {
    nobridge::pbn::Reader reader(
        "files/RB_220702123558SistaChansen_full.pbn.txt");

    nobridge::pbn::Parser parser(reader);
    nobridge::pbn::GameList gl = parser.run();

    // find tag
    auto tl = gl.begin();
    auto it = nobridge::pbn::find_tag((*tl).begin(), (*tl).end(), "event");
    if (it != (*tl).end()) {
        std::cout << (*it)->name << ": " << (*it)->value << std::endl;
    }

    reader.close();
}
