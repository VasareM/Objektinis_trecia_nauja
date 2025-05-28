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
/*
v5 = v3;
    REQUIRE(v5.size() == 3);
    REQUIRE(v5[2] == 7);

*/
TEST_CASE("Testas at()")
{
    Vector<int> v{1, 2, 3};
    REQUIRE_NOTHROW(v.at(2));
    REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
}
TEST_CASE("operator[] testas, priskyrimas ir taisymas")
{
    Vector<int> v{1, 2, 3};
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);

    v[1]=250;
    REQUIRE(v[1] == 250);
    // operatorius ir dirba su indeksais
}
TEST_CASE("front(), back() testas")
{
    Vector<int> v{1, 2, 3};
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);

    REQUIRE(v.front() == 1);
    REQUIRE(v.back() == 3);
}
/*
at
operator[]
front
back
size
capacity
empty
max_size
reserve
shrink_to_fit
*/
TEST_CASE("push_back, pop_back, clear test")
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    REQUIRE(v.size() == 3);
    REQUIRE(v.back() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);

    v.pop_back();
    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == 2);

    v.clear();
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty());
}

// resize
// resize

/*
insert
insert
erase
erase
assign
assign
swap
begin
begin
cbegin
end
end
cend
rbegin
rbegin
rbegin
rend
rend
rend
get_allocator
data

*/
