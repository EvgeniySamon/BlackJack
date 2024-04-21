#include<Blackjeck.h>

bool BlackJeck::GetDealerMove() const{
    return DealerMove;
}
size_t BlackJeck::GetKolvoCards() const{
    return cards.GetKolvoCards();
}

size_t BlackJeck::GetI() const{
    return i;
}

size_t BlackJeck::GetKolvoCardsInBita() const{
    return cards.GetKolvoCardsInBita();
}

vector<pair<Deck, Chips>> BlackJeck::GetCardsPlayer() const{
    return CardsPlayer;
}
Deck BlackJeck::GetCardsDiler() const{
    return CardsDiler;
}
pair<size_t, bool> BlackJeck::GetSumPoint(const Deck& d) const{
    vector<size_t> summ = {0};
    for(size_t j = 0; j < d.GetCards().size(); ++j){
        if(size_t a = d.GetCards().at(j).GetNominalBlackJack() != 1){
            for(auto& sum : summ){
                sum += a;
            }
        }
    }
    
}
void BlackJeck::PlayDealer(){

}
bool BlackJeck::can(const string& dei){
    switch (dei[0])
    {
    case '1':{
        DealerMove = 1;
        PlayDealer();
        return 1;
    }
    case '2':{

    }


    case '3':
    break;
    
    default:
        break;
    }
}
ostream& operator << (ostream& out, const BlackJeck& a){
    out << "\nКарт в колоде осталось: " << a.GetKolvoCards() << "\nКарт в бите: " << a.GetKolvoCardsInBita()
        << "\nКарт до перемешивания колоды: " << 291 - a.GetKolvoCards() << "\n";
    if(a.GetDealerMove()){
        out << "Карты дилера: " << a.GetCardsDiler() << "\n";
    }else{
        out << "Карты дилера: " << a.GetCardsDiler().GetCard(0) << "  |* *|\n";
    }
    out << "Ваши карты:\n";
    size_t i = 0;
    for(const auto& elem : a.GetCardsPlayer()){
        out << elem.first << " сумма очков: " << ""
        << " Ставка: " << elem.second << "\n";
        if(a.GetI() == i){
            out << "Дейстивия: 1.Хватит  2.Ещё  3.Удвоить  4. Разделить" << "\n";
        }
        ++i;
    }

    return out;
} 

void BlackJeck::PlayBlackjack(){
    size_t KolvoHand; i = 0;
    CardsDiler.DeckClear(); CardsPlayer.clear();
    cout << "Ваши ставки(глаз мой радуют всегда), " << player->name << ",(ставка на все руки одинакова)\n";
    auto para = player->DoBet();
    for(size_t i = 0; i < para.second; ++i){
        CardsPlayer.push_back({Deck({cards.GetCard(), cards.GetCard()}), para.first});
    }
    CardsDiler = Deck({cards.GetCard(), cards.GetCard()});
    cout << *this;
    for(const auto& elem : CardsPlayer){
        
    }
    string dei;
    while(can(dei)){

    }
    cin >> dei;
}