#include<Deck.h>

void Deck::push_back(const Card& card){
    cards.push_back(card);
}

vector<Card> Deck::GetCards() const{
    return cards;
}

void Deck::DeckClear(){
    cards.clear();
    i = 0; Mix = 0;
}

size_t Deck::GetKolvoCards() const{
    return cards.size() - i;
}

size_t Deck::GetKolvoCardsInBita() const{
    return i;
}

size_t Deck::GetMix() const{
    return Mix;
}

void Deck::deck_52_Rand(size_t Quantity = 1, double per = 1.0){
    static const vector<Card>cards_52 = {
        {2, 'К'}, {2, 'Ч'}, {2, 'П'}, {2, 'Б'},
        {3, 'К'}, {3, 'Ч'}, {3, 'П'}, {3, 'Б'},
        {4, 'К'}, {4, 'Ч'}, {4, 'П'}, {4, 'Б'},
        {5, 'К'}, {5, 'Ч'}, {5, 'П'}, {5, 'Б'},
        {6, 'К'}, {6, 'Ч'}, {6, 'П'}, {6, 'Б'},
        {7, 'К'}, {7, 'Ч'}, {7, 'П'}, {7, 'Б'},
        {8, 'К'}, {8, 'Ч'}, {8, 'П'}, {8, 'Б'},
        {9, 'К'}, {9, 'Ч'}, {9, 'П'}, {9, 'Б'},
        {10, 'К'}, {10, 'Ч'}, {10, 'П'}, {10, 'Б'},
        {11, 'К'}, {11, 'Ч'}, {11, 'П'}, {11, 'Б'},
        {12, 'К'}, {12, 'Ч'}, {12, 'П'}, {12, 'Б'},
        {13, 'К'}, {13, 'Ч'}, {13, 'П'}, {13, 'Б'}
    };
    QuantityDecks = Quantity; cards = cards_52 * QuantityDecks; peremesh = per; Mix = size_t(cards.size() * peremesh); 
    random_shuffle(cards.begin(), cards.end());
}

Card Deck::GetCard(bool a = 1){   
    if(i = Mix && a){
        deck_52_Rand();
        i = 0;
        cout << "\nПеремешивание колоды!!!\n";
    }
    ++i;
    return cards.at(i-1);
}

ostream& operator << (ostream& out, const Deck& a){
    for(const auto& elem : a.GetCards()){
        out << elem << " ";
    }
    return out;
} 