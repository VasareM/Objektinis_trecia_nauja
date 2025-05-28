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

    REQUIRE(v.front() == 1);
    REQUIRE(v.back() == 3);
}
TEST_CASE("size(), capacity(), reserve(), shrink_to_fit() testas")
{
    Vector<int> v{1, 2, 3};
    REQUIRE(v.size() == 3);

    REQUIRE(v.capacity() >= 3); // capacity should be at least 3

    v.reserve(10);
    REQUIRE(v.capacity() >= 10); // after reserve, capacity should be at least 10

    v.push_back(4);
    REQUIRE(v.size() == 4);
    REQUIRE(v.capacity() >= 10); // capacity should not decrease after push_back

    v.shrink_to_fit();
    REQUIRE(v.capacity() == v.size()); // after shrink_to_fit, capacity == size
}
TEST_CASE("max_size() test")
{
    Vector<int> v{1, 2, 3};
    REQUIRE(v.max_size() > 1000000);
    REQUIRE(v.max_size() >= v.size());
    //max_size - ne mažesnis už size(), didesnis už labai didelį skaičių
}
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
TEST_CASE("resize() testai")
{
    Vector<int> v{1, 2, 3};
    // padidinama rankiniu būdu:
    v.resize(5);
    REQUIRE(v.size() == 5);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 0);
    REQUIRE(v[4] == 0);
    //sumažinama iki skč:
    v.resize(3);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    //padidinama iki skaičiaus, visi papildomi antro skč
    v.resize(5, 10);
    REQUIRE(v.size() == 5);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 10);
    REQUIRE(v[4] == 10);
}
TEST_CASE("insert() tests")
{
    Vector<int> v{1, 2, 3};
    v.insert(v.begin(), 0);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 1);

    v.insert(v.begin()+2, 40);
    REQUIRE(v.size() == 5);
    REQUIRE(v[2] == 40);

    v.insert(v.end(), 50);
    REQUIRE(v.size() == 6);
    REQUIRE(v[5] == 50);

    int sarasas[] = {16, 17, 18};
    v.insert(v.begin()+3, sarasas, sarasas+3);
    REQUIRE(v.size() == 9);
    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 1);
    REQUIRE(v[2] == 40);
    REQUIRE(v[3] == 16);
    REQUIRE(v[4] == 17);
    REQUIRE(v[5] == 18);
    REQUIRE(v[6] == 2);
    REQUIRE(v[7] == 3);
    REQUIRE(v[8] == 50);
}
/*
TEST_CASE("")
{
    Vector<int> v{1, 2, 3};

    REQUIRE();
}

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
