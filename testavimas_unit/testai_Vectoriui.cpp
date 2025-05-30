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
////////// rei6kia

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
//////// tsgw?

    // Destructor is implicitly tested (no crash, no leak)
}
TEST_CASE("Copy konstruktoriaus testas")
{
    Vector<int> v1{1, 2, 3};
    // Copy konstruktorius
    Vector<int> v2 = v1;
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);
}
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

    REQUIRE(v.capacity() >= 3);

    v.reserve(10);
    REQUIRE(v.capacity() >= 10);
    
    v.push_back(4);
    REQUIRE(v.size() == 4);
    REQUIRE(v.capacity() >= 10); // capacity nesumazeja po push_back

    v.shrink_to_fit();
    REQUIRE(v.capacity() == v.size()); // po shrink_to_fit, capacity = size
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
TEST_CASE("erase() testai")
{
    Vector<int> v{1, 2, 3, 4, 5};
    v.erase(v.begin() + 2);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 4);
    REQUIRE(v[3] == 5);

    v.erase(v.begin() + 1, v.begin() + 3); // išima [1] ir [2]
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 5);

    v.erase(v.begin(), v.end());
    REQUIRE(v.size() == 0);
}
TEST_CASE("assign() testai")
{
    Vector<int> v{1, 2, 3, 4, 5};
    v.assign(7, 10);
    REQUIRE(v.size() == 7);
    for (int i=0; i<7; ++i)
    {
        REQUIRE(v[i] == 10);
    }

    Vector<int> v1{1, 2, 3, 4, 5};
    int sarasas[]={7, 8, 9};
    v1.assign(sarasas+1, sarasas+3);
    REQUIRE(v1.size() == 2);
    REQUIRE(v1[0] == 8);
    REQUIRE(v1[1] == 9);
}
TEST_CASE("swap() testas")
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{4, 5};
    
    v1.swap(v2);

    REQUIRE(v1.size() == 2);
    REQUIRE(v1[0] == 4);
    REQUIRE(v1[1] == 5);

    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);
}
TEST_CASE("begin ir end, ir c, ir r testai")
{
    Vector<int> v{1, 2, 3};

    // Test begin/end (forward iteration)
    int expected[] = {1, 2, 3};
    int i = 0;
    for (auto it = v.begin(); it != v.end(); ++it, ++i)
        REQUIRE(*it == expected[i]);
    REQUIRE(i == 3);

    // Test cbegin/cend (const forward iteration)
    i = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it, ++i)
        REQUIRE(*it == expected[i]);
    REQUIRE(i == 3);

    // Test rbegin/rend (reverse iteration)
    int expected_rev[] = {3, 2, 1};
    i = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it, ++i)
        REQUIRE(*it == expected_rev[i]);
    REQUIRE(i == 3);

    // Test crbegin/crend (const reverse iteration)
    i = 0;
    for (auto it = v.crbegin(); it != v.crend(); ++it, ++i)
        REQUIRE(*it == expected_rev[i]);
    REQUIRE(i == 3);
}
TEST_CASE("data() testas")
{
    Vector<int> v{5, 6, 7};
    REQUIRE(v.data() == &v[0]);      // data() points to first element
    *v.data() = 42;
    REQUIRE(v[0] == 42);             // modifying through data() works
}
TEST_CASE("get_allocator() testas")
{
    Vector<int> v;
    auto alloc = v.get_allocator();
    int* p = alloc.allocate(1);
    alloc.construct(p, 123);
    REQUIRE(*p == 123);
    alloc.destroy(p);
    alloc.deallocate(p, 1);
}
TEST_CASE("Copy constructor for Vector") {
    Vector<int> v1{1, 2, 3, 4};
    Vector<int> v2 = v1; // copy constructor
    REQUIRE(v2.size() == v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        REQUIRE(v2[i] == v1[i]);
    }
    // Changing v2 does not affect v1
    v2[0] = 100;
    REQUIRE(v1[0] == 1);
    REQUIRE(v2[0] == 100);
}

TEST_CASE("Move constructor for Vector") {
    Vector<int> v1{10, 20, 30};
    Vector<int> v2 = std::move(v1); // move constructor
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 10);
    REQUIRE(v2[1] == 20);
    REQUIRE(v2[2] == 30);
    REQUIRE(v1.size() == 0); // v1 should be empty after move
}

TEST_CASE("Copy assignment for Vector") {
    Vector<int> v1{5, 6, 7};
    Vector<int> v2;
    v2 = v1; // copy assignment
    REQUIRE(v2.size() == v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        REQUIRE(v2[i] == v1[i]);
    }
    // Changing v2 does not affect v1
    v2[1] = 99;
    REQUIRE(v1[1] == 6);
    REQUIRE(v2[1] == 99);
}

TEST_CASE("Move assignment for Vector") {
    Vector<int> v1{11, 22, 33};
    Vector<int> v2;
    v2 = std::move(v1); // move assignment
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 11);
    REQUIRE(v2[1] == 22);
    REQUIRE(v2[2] == 33);
    REQUIRE(v1.size() == 0); // v1 should be empty after move
}

/*
TEST_CASE("")
{
    Vector<int> v{1, 2, 3};

    REQUIRE();
}
*/
