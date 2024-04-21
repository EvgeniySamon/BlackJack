#pragma once
#include<Chips.h>
#include<string>
#include<windows.h>
using namespace std;

class Player{  
    Chips chips;
public:
    string name;
    Player(const string& na, const Chips& ba = Chips()): name(na), chips(ba){}
    
    Chips GetChipsPlayer();

    void profit(const Chips& prof);

    void decline(const Chips& dec);

    pair<Chips, size_t> DoBet();
};