#include "BlackJeck.h"

bool BlackJeck::GetDealerMove() const {
    return DealerMove;
}
size_t BlackJeck::GetKolvoCards() const {
    return cards.GetKolvoCards();
}

size_t BlackJeck::GetI() const {
    return i;
}

size_t BlackJeck::GetKolvoCardsInBita() const {
    return cards.GetKolvoCardsInBita();
}

vector<pair<Deck, Chips>> BlackJeck::GetCardsPlayer() const {
    return CardsPlayer;
}

Deck BlackJeck::GetCardsDiler() const {
    return CardsDiler;
}

Player* BlackJeck::GetPlayer() const{
    return player;
}

void BlackJeck::BJ_move(const string& dei) {
    switch (dei[0])
    {
    case '1': {
        ++i;
        return;
    }
    case '2': {
        CardsPlayer[i].first.push_back(cards.GetCard());
        if(CardsPlayer[i].first.GetSumPoint() > 21)
            ++i;
        return; 
    }

    case '3':{
        if(CardsPlayer[i].first.GetCards().size() != 2 ||
        !player->GetChipsPlayer().ChipsReserve(CardsPlayer[i].second) || 
        CardsPlayer[i].first.GetSumPoint() == 21){
            color(4);
            cout << "Недостаточно средств или у вас не две карты или комбинация = 21\n";
            color(15);
            system("pause");
            return;
        }
        player->decline(CardsPlayer[i].second);
        CardsPlayer[i].second = 2 * CardsPlayer[i].second;
        CardsPlayer[i].first.push_back(cards.GetCard());
        ++i;
        return;
    }

    case '4':{
        if(CardsPlayer[i].first.GetCards().size() != 2 ||
        !player->GetChipsPlayer().ChipsReserve(CardsPlayer[i].second) ||
        CardsPlayer[i].first.GetCards()[0].GetNominalBlackJack() != CardsPlayer[i].first.GetCards()[1].GetNominalBlackJack() ||
        (CardsPlayer[i].first.GetCards()[0].GetNominalBlackJack() == 11 && CardsPlayer[i].first.GetCards()[1].GetNominalBlackJack() == 11)){
            color(4);
            cout << "Недостаточно средств или у вас не две карты или карты не одинаковы или у вас 2 туза!!!\n";
            color(15);
            system("pause");
            return;
        }
        auto para = CardsPlayer[i];
        CardsPlayer.erase(CardsPlayer.begin()+i);
        pair<Deck, Chips> par1 = {Deck({para.first.GetCards()[1], cards.GetCard()}), para.second};
        CardsPlayer.insert(CardsPlayer.begin()+i, par1);
        pair<Deck, Chips> par2 = {Deck({para.first.GetCards()[0], cards.GetCard()}), para.second};
        CardsPlayer.insert(CardsPlayer.begin()+i, par2);
    }

    default:
        break;
    }
    return;
}

ostream& operator << (ostream& out, const BlackJeck& a) {
    out << "Ваш баланс: " << a.GetPlayer()->GetChipsPlayer()
        << "\nКарт в колоде осталось: " << a.GetKolvoCards() << "    Карт в бите: " << a.GetKolvoCardsInBita()
        << "    Карт до перемешивания колоды: " << a.GetKolvoCards() - 93 << "\n\n";
    if (a.GetDealerMove()) {
        out << "Карты дилера:\n" << a.GetCardsDiler() << "  сумма очков: " << a.GetCardsDiler().GetSumPoint();
    }
    else {
        out << "Карты дилера:\n" << a.GetCardsDiler().GetCards()[0] << " |* *|  сумма очков: " << a.GetCardsDiler().GetCards()[0].GetNominalBlackJack();
    }
    out << "\n\nВаши карты:\n";
    size_t i = 0;
    for (const auto& elem : a.GetCardsPlayer()) {
        out << elem.first << " сумма очков: " << elem.first.GetSumPoint();
            if(elem.first.GetSumPoint()>21 || (a.GetDealerMove() && elem.first.GetSumPoint() < a.GetCardsDiler().GetSumPoint() && a.GetCardsDiler().GetSumPoint() < 22)){
                color(4);
                out << "\tРука проиграна(";
                color(15);
            }else if(a.GetDealerMove() && (elem.first.GetSumPoint() > a.GetCardsDiler().GetSumPoint() || a.GetCardsDiler().GetSumPoint() > 21)){
                color(2);
                out << "\tРука выиграна!!";
                color(15);
            }else if(a.GetDealerMove() && elem.first.GetSumPoint() == a.GetCardsDiler().GetSumPoint()){
                color(11);
                out << "\tНичья)";
                color(15);
            }
            out << "    Ставка: " << elem.second << "\n";
        if (a.GetI() == i && !a.GetDealerMove()) {
            color(3);
            out << "Дейстивия: 1.Хватит  2.Ещё  3.Удвоить  4. Разделить" << "\n";
            color(15);
        }
        ++i;
    }

    return out;
}

Chips BlackJeck::Win(){
    size_t w = CardsDiler.GetSumPoint();
    if(w > 21)
        w = 0;
    Chips win;
    for(const auto& elem : CardsPlayer){
        if(elem.first.GetSumPoint() > w && elem.first.GetSumPoint() < 22){
            player->profit(2 * elem.second);
            win.profit(2 * elem.second);
        }else if(elem.first.GetSumPoint() == w){
            player->profit(elem.second);
            win.profit(elem.second);
        }
    }
    return win;
}

void BlackJeck::PlayDealer() {
    cout << *this;
    color(3);
    cout << "Ход дилера...\n";
    color(15);
    system("pause");
    while(CardsDiler.GetSumPoint() < 17){
        system("Cls");
        CardsDiler.push_back(cards.GetCard());
        cout << *this;
        color(3);
        cout << "Ход дилера...\n";
        color(15);
        system("pause");
    }
    system("Cls");
    cout << *this;
    color(4);
    cout << "Окончательный результат!!!\n";
    color(15);
    system("pause");
}

void BlackJeck::DealerBlackJeck(){
    for(auto& elem : CardsPlayer){
        while(elem.first.GetSumPoint() < 21){
            elem.first.push_back(cards.GetCard());
            system("Cls");
            cout << *this;
            color(3);
            cout << "Вы добираете карты...\n";
            color(15);
            system("pause");
        }
    }
    system("Cls");
    cout << *this;
    color(4);
    cout << "Окончательный результат!!!\n";
    color(15);
    system("pause");
}

void BlackJeck::PlayBlackjack() {
    i = 0; DealerMove = 0;
    CardsDiler.DeckClear(); CardsPlayer.clear();
    cout << "Ваши ставки господа(глаз мой радуют всегда), " << player->name << ":\nВаш баланс(ставка на все руки одинакова): ";
    auto para = player->DoBet();
    system("Cls");
    for (size_t j = 0; j < para.second; ++j) {
        CardsPlayer.push_back({ Deck({cards.GetCard(), cards.GetCard()}), para.first });
    }
    CardsDiler = Deck({ cards.GetCard(), cards.GetCard() });
    if(CardsDiler.GetSumPoint() == 21){
        DealerMove = 1;
        DealerBlackJeck();
        system("Cls");
        color(2);
        cout << "Ваш выигрыш:\n" << Win() << "\n";
        color(15);
        return;
    }
    string dei;
    while(i < CardsPlayer.size()){
        cout << *this;
        cin >> dei;
        BJ_move(dei);
        system("Cls");
    }
    DealerMove = 1;
    PlayDealer();
    system("Cls");
    color(2);
    cout << "Ваш выигрыш:\n" << Win() << "\n";
    color(15);
}

void BlackJeck::Game(){
    player->BuyBalance();
    string vibor;
    do{
        system("Cls"); 
        PlayBlackjack();
        cout << "выйти из стола?(2 - докупить фишек/ 1 - да/ 0 - нет): ";
        cin.ignore();
        getline(cin, vibor);
        if(vibor[0] == '2'){
            player->BuyBalance();
        }
    }while(vibor != "1");
}

void color(const unsigned short a) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, a);
}