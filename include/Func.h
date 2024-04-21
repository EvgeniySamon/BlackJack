#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <Card.h>

using namespace std;

template<typename T>
vector<T> operator+=(vector<T>& a, const vector<T>& other){
    for(auto elem : other){
        a.push_back(elem);
    }
    return a;
}

template<typename T2>
vector<T2> operator*(const vector<T2>& a, long long other){
    vector<T2> res;
    for(size_t i = 0; i < other; ++i){
        res += a;
    }
    return res;
}