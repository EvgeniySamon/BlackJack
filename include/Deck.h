#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <Card.h>
#include<Func.h>
using namespace std;

class Deck{
    vector<Card> cards;
    size_t i = 0, Mix = cards.size();
    double peremesh = 1.0;
    size_t QuantityDecks = 1;
    
public:
    Deck(vector<Card> Card = {}): cards(Card){}

    void push_back(const Card& card);

    vector<Card> GetCards() const;

    void DeckClear();

    size_t GetKolvoCards() const;

    size_t GetKolvoCardsInBita() const;

    size_t GetMix() const;

    void deck_52_Rand(size_t Quantity = 1, double per = 1.0);

    Card GetCard(bool a = 1);

};

ostream& operator << (ostream& out, const Deck& a);