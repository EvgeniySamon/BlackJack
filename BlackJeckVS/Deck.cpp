#include "Deck.h"

void Deck::push_back(const Card& card) {
    cards.push_back(card);
}

vector<Card> Deck::GetCards() const {
    return cards;
}

void Deck::DeckClear() {
    cards.clear();
    i = 0; Mix = 0;
}

size_t Deck::GetKolvoCards() const {
    return cards.size() - i;
}

size_t Deck::GetKolvoCardsInBita() const {
    return i;
}

size_t Deck::GetMix() const {
    return Mix;
}

void Deck::deck_52_Rand(size_t Quantity, double per) {
    static const vector<Card>cards_52 = {
        {2, '�'}, {2, '�'}, {2, '�'}, {2, '�'},
        {3, '�'}, {3, '�'}, {3, '�'}, {3, '�'},
        {4, '�'}, {4, '�'}, {4, '�'}, {4, '�'},
        {5, '�'}, {5, '�'}, {5, '�'}, {5, '�'},
        {6, '�'}, {6, '�'}, {6, '�'}, {6, '�'},
        {7, '�'}, {7, '�'}, {7, '�'}, {7, '�'},
        {8, '�'}, {8, '�'}, {8, '�'}, {8, '�'},
        {9, '�'}, {9, '�'}, {9, '�'}, {9, '�'},
        {10, '�'}, {10, '�'}, {10, '�'}, {10, '�'},
        {11, '�'}, {11, '�'}, {11, '�'}, {11, '�'},
        {12, '�'}, {12, '�'}, {12, '�'}, {12, '�'},
        {13, '�'}, {13, '�'}, {13, '�'}, {13, '�'},
        {14, '�'}, {14, '�'}, {14, '�'}, {14, '�'}
    };
    QuantityDecks = Quantity; cards = (cards_52 * QuantityDecks); peremesh = per; Mix = size_t(cards.size() * peremesh);
    random_shuffle(cards.begin(), cards.end());
}

Card Deck::GetCard(bool a) {
    if (i == Mix && a) {
        deck_52_Rand();
        i = 0;
        cout << "\n������������� ������!!!\n";
    }
    ++i;
    return cards.at(i - 1);
}

size_t Deck::GetSumPoint() const{
    vector<size_t> summ = {}; size_t i = 0, tuz = 0, Tecushtuz = 0;
    do{
        summ.push_back(0); Tecushtuz = tuz;
        for (const auto& elem : cards){
            if(elem.GetNominalBlackJack() != 11 || Tecushtuz == 0){
                summ[i] += elem.GetNominalBlackJack();
            }else{
                ++summ[i];
                --Tecushtuz;
            }
        }
        ++i; ++tuz;
    }while(summ[i-1] > 21 && tuz < cards.size()+1);
    sort(summ.begin(), summ.end());
    auto elem = lower_bound(begin(summ), end(summ), 22);
    if(elem != summ.begin()){
        --elem;
    }  
    return *elem;
}

ostream& operator << (ostream& out, const Deck& a) {
    for (const auto& elem : a.GetCards()) {
        out << elem << " ";
    }
    return out;
}