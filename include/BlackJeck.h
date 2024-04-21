#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <Card.h>
#include<Func.h>
#include<Deck.h>
#include<Chips.h>
#include<Player.h>

using namespace std;

class BlackJeck{
    bool DealerMove = 0;
    Deck cards;
    Player* player;
    Deck CardsDiler;
    vector<pair<Deck, Chips>> CardsPlayer;
    size_t i = 0;
public:
    BlackJeck(Player* pl): player(pl){cards.deck_52_Rand(8, 0.7);}

    bool GetDealerMove() const;

    size_t GetKolvoCards() const;

    size_t GetI() const;

    size_t GetKolvoCardsInBita() const;

    vector<pair<Deck, Chips>> GetCardsPlayer() const;

    Deck GetCardsDiler() const;

    pair<size_t, bool> GetSumPoint(const Deck& d) const;

    void PlayDealer();

    bool can(const string& dei);

    friend ostream& operator << (ostream& out, const BlackJeck& a);

    void PlayBlackjack();

};
