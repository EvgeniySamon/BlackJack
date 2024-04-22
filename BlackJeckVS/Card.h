#pragma once

#include <iostream>
#include <windows.h>
#include <map>
#include <string>
using namespace std;

class Card{
    int nominal;
    char suit;

    void norm();
public:
    Card(int nom = 2, char su = 'Ê') : nominal(nom), suit(su) { norm(); }

    int GetNominal() const;

    int GetNominalBlackJack() const;

    char GetSuit() const;

    string GetPic() const;
};

ostream& operator << (ostream& out, const Card& a);