#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>

#include "parser.h"
#include "reader.h"

TEST(ReaderTest, HandlesFile) {
    nobridge::pbn::Reader reader(
        "files/RB_220702123558SistaChansen_full.pbn.txt");

    EXPECT_TRUE(reader.ok()) << "ERROR: reader.ok() is false";
    EXPECT_FALSE(reader.eof()) << "ERROR: reader.eof() is true";
    EXPECT_TRUE(reader.nextLine().length() > 0)
        << "ERROR: reader.nextLine().length() is 0";

    reader.close();
}

TEST(ParserTest, HandlesReader) {
    nobridge::pbn::Reader reader(
        "files/RB_220702123558SistaChansen_full.pbn.txt");

    nobridge::pbn::Parser parser(reader);
    parser.run();
}
