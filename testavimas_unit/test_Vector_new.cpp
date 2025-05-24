#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Vector_new.h"

TEST_CASE("Vector basic construction and assignment") {
    Vector<int> v1;
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() == 0);
    REQUIRE(v1.empty());

    Vector<int> v2(5);
    REQUIRE(v2.size() == 5);
    for (int i = 0; i < 5; ++i) REQUIRE(v2[i] == 0);

    Vector<int> v3(3, 7);
    REQUIRE(v3.size() == 3);
    for (int i = 0; i < 3; ++i) REQUIRE(v3[i] == 7);

    Vector<int> v4{1, 2, 3};
    REQUIRE(v4.size() == 3);
    REQUIRE(v4[0] == 1);
    REQUIRE(v4[1] == 2);
    REQUIRE(v4[2] == 3);

    Vector<int> v5 = v4;
    REQUIRE(v5.size() == 3);
    REQUIRE(v5[1] == 2);

    v5 = v3;
    REQUIRE(v5.size() == 3);
    REQUIRE(v5[2] == 7);
}

TEST_CASE("Vector push_back, pop_back, clear, and resize") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    REQUIRE(v.size() == 3);
    REQUIRE(v.back() == 3);

    v.pop_back();
    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == 2);

    v.clear();
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty());

    v.resize(4, 9);
    REQUIRE(v.size() == 4);
    for (int i = 0; i < 4; ++i) REQUIRE(v[i] == 9);

    v.resize(2);
    REQUIRE(v.size() == 2);
}

TEST_CASE("Vector insert, erase, assign, swap") {
    Vector<int> v{1, 2, 3, 4};
    v.insert(v.begin() + 2, 99);
    REQUIRE(v.size() == 5);
    REQUIRE(v[2] == 99);

    v.erase(v.begin() + 2);
    REQUIRE(v.size() == 4);
    REQUIRE(v[2] == 3);

    v.assign(3, 7);
    REQUIRE(v.size() == 3);
    for (int i = 0; i < 3; ++i) REQUIRE(v[i] == 7);

    int arr[] = {10, 20, 30, 40};
    v.assign(arr, arr + 4);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 10);
    REQUIRE(v[3] == 40);

    Vector<int> v2{100, 200};
    v.swap(v2);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 100);
    REQUIRE(v2.size() == 4);
    REQUIRE(v2[1] == 20);
}

TEST_CASE("Vector erase and insert with ranges") {
    Vector<int> v{1, 2, 3, 4, 5, 6};
    v.erase(v.begin() + 1, v.begin() + 4); // remove 2,3,4
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 5);
    REQUIRE(v[2] == 6);

    int arr[] = {7, 8, 9};
    v.insert(v.begin() + 1, arr, arr + 3);
    REQUIRE(v.size() == 6);
    REQUIRE(v[1] == 7);
    REQUIRE(v[3] == 9);
}

TEST_CASE("Vector iterators and reverse iterators") {
    Vector<int> v{1, 2, 3};
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) sum += *it;
    REQUIRE(sum == 6);

    sum = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it) sum += *it;
    REQUIRE(sum == 6);

    REQUIRE(*v.cbegin() == 1);
    REQUIRE(*(v.cend() - 1) == 3);
    REQUIRE(*v.crbegin() == 3);
    REQUIRE(*(v.crend() - 1) == 1);
}

TEST_CASE("Vector at() throws on out of range") {
    Vector<int> v{1, 2, 3};
    REQUIRE_NOTHROW(v.at(2));
    REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
}
