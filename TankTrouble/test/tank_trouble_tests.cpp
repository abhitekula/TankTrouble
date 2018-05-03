#include <iostream>

#define CATCH_CONFIG_MAIN

#include "catch.h"
#include "../src/frequency_counter.cpp"

void SetUp() {
    ifstream text("../test/test.txt");
    cin.rdbuf(text.rdbuf());

    FrequencyCounter();
    cin.clear();
}

TEST_CASE("parseMultipleSpacesTest") {
    //a       a           a a a a a a
    // a a
    SetUp();

    REQUIRE(words_map["a"] == 10);
}

TEST_CASE("parseApostropheTest") {
    //b's b's b's b's b b b b b
    SetUp();

    REQUIRE(words_map["b"] == 5);
    REQUIRE(words_map["b's"] == 5);
}

TEST_CASE("ignoreSpecialCharactersTest") {
    //c! c@ c# c$ c% c^ c& c*
    //d( d) d- d+ d_ d= d`
    SetUp();

    REQUIRE(words_map["c"] == 8);
    REQUIRE(words_map["d"] == 7);
}

TEST_CASE("ignoreSpecialCharactersInMiddleTest") {
    //e`e e~e e/e e?e e:e e"e
    SetUp();

    REQUIRE(words_map["ee"] == 6);
}

TEST_CASE("addToMapTest") {
    //Checks whether the rest of the words were properly added.
    SetUp();

    REQUIRE(words_map["f"] == 5);
    REQUIRE(words_map["g"] == 4);
    REQUIRE(words_map["h"] == 3);
    REQUIRE(words_map["i"] == 2);
    REQUIRE(words_map["j"] == 1);
}

TEST_CASE("getMostCommonWordsTest") {
    SetUp();

    vector<string> expected = {"a", "b", "b's", "c", "d", "ee", "f", "g", "h",
                               "i"};
    REQUIRE(expected == most_common_words);
}