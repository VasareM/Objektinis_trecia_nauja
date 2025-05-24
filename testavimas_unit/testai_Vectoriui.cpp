#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Vector_new.h"

TEST_CASE("Konstruktorių testai")
{
    // Pagrindinis konstruktorius
    Vector<int> v1;
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() == 0);

    // Konstruktorius su size_type
    Vector<int> v2(5);
    REQUIRE(v2.size() == 5);
    for (int i = 0; i < 5; ++i) REQUIRE(v2[i] == 0);
////////// i6siai6kint k1 rei6kia

    // Konstruktorius su size_type ir value_type
    Vector<int> v3(5, 2);
    REQUIRE(v3.size() == 5);
    for (int i = 0; i < 5; ++i) REQUIRE(v3[i] == 2);

    // Initializer list constructor
    Vector<int> v4{1, 2, 3};
    REQUIRE(v4.size() == 3);
    REQUIRE(v4[0] == 1);
    REQUIRE(v4[1] == 2);
    REQUIRE(v4[2] == 3);
//////// tsg wtf?

    // Destructor is implicitly tested (no crash, no leak)
}
TEST_CASE("AA")
{
    Vector<int> v1{1, 2, 3};
    // Copy konstruktorius
    Vector<int> v2 = v1;
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);
}