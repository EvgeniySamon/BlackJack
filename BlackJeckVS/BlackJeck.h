#pragma once
#include <iostream>
#include <windows.h>
#include <set>
#include <vector>
#include "Card.h"
#include "Func.h"
#include "Deck.h"
#include "Chips.h"
#include "Player.h"

using namespace std;

class BlackJeck {
    bool DealerMove = 0;
    Deck cards;
    Player* player;
    Deck CardsDiler;
    vector<pair<Deck, Chips>> CardsPlayer;
    size_t i = 0;   
    void PlayDealer();

    void BJ_move(const string& dei);

    void PlayBlackjack();

    void DealerBlackJeck();

    Chips Win();
public:
    BlackJeck(Player* pl) : player(pl) { cards.deck_52_Rand(6, 0.7); }

    bool GetDealerMove() const;

    size_t GetKolvoCards() const;

    size_t GetI() const;

    size_t GetKolvoCardsInBita() const;

    vector<pair<Deck, Chips>> GetCardsPlayer() const;

    Deck GetCardsDiler() const;

    Player* GetPlayer() const;

    friend ostream& operator << (ostream& out, const BlackJeck& a);

    void Game();
};

void color(const unsigned short a);