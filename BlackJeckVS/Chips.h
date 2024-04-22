#pragma once
#include <iostream>
#include <windows.h>
#include <map>
#include <cmath>
using namespace std;


class Chips {
    map<size_t, size_t> chips;
    size_t balance;

    void norm();

public:
    Chips(const map<size_t, size_t>& EnChips = {}) : chips(EnChips) { norm(); }

    map<size_t, size_t> GetChips() const;

    size_t GetBalance() const;

    size_t SummChips(const Chips& chips_other);

    friend ostream& operator << (ostream& out, const Chips& a);

    friend istream& operator >> (istream& in, Chips& a);

    void BuyBalance();

    void profit(const Chips& prof);

    void decline(const Chips& dec);

    bool ChipsReserve(const Chips& chips_other) const;
};

Chips operator*(long long other, const Chips& a);