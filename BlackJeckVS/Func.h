#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
vector<T> operator+=(vector<T>& a, const vector<T>& other) {
    for (auto elem : other) {
        a.push_back(elem);
    }
    return a;
}

template<typename T2>
vector<T2> operator*(const vector<T2>& a, size_t other) {
    vector<T2> res;
    for (size_t i = 0; i < other; ++i) {
        res += a;
    }
    return res;
}