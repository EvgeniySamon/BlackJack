#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void color(const unsigned short int a){
    SetConsoleTextAttribute(hConsole, a);
}

template<typename T>
vector<T> operator+=(vector<T>& a, const vector<T>& other){
    for(auto elem : other){
        a.push_back(elem);
    }
    return a;
}

template<typename T2>
vector<T2> operator*(const vector<T2>& a, long long other){
    vector<T2> res;
    for(size_t i = 0; i < other; ++i){
        res += a;
    }
    return res;
}

class card{
    int nominal;
    char suit;
public:
    card(int nom = 2, char su = 'К'): nominal(nom), suit(su){norm();}
    void norm(){
        if(nominal > 14){
            nominal = 12;
        }else if(nominal < 2){
            nominal = 2;
        }
        if(suit != 'К' || suit != 'Ч' || suit != 'П' || suit != 'Б'){
            suit = 'К';
        }
    }
    int GetNominal() const{
        return nominal;
    }
    int GetNominal_BlackJack() const{
        if(nominal < 10)
            return nominal;
        else if(nominal != 13){
            return 10;
        }else
            return 1;
    }
    char GetSuit() const{
        return suit;
    }
    char GetPic() const{
        static const map<int, char> pic = {{2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'},
        {10, 'J'}, {11, 'Q'}, {12, 'K'}, {13, 'A'}, {14, 'Д'}};
        return pic.at(nominal);
    }
};

class deck{
    vector<card> cards;
    size_t i = 0, Mix = cards.size();
    double peremesh = 1.0;
    size_t QuantityDecks = 1;
public:
    deck(vector<card> Card = {}): cards(Card){}
    void push_back(const card& Card){
        cards.push_back(Card);
    }
    vector<card> GetCards(){
        return cards;
    }
    void DeckClear(){
        cards.clear();
        i = 0; Mix = 0;
    }
    size_t GetKolvoCards() const{
        return cards.size() - i;
    }
    size_t GetKolvoCardsInBita() const{
        return i;
    }
    size_t GetMix() const{
        return Mix;
    }
    void deck_52_Rand(size_t Quantity = 1, double per = 1.0){
        static const vector<card>cards_52 = {
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
    card GetCard(){
        if(i = Mix){
            deck_52_Rand();
            i = 0;
            cout << "\nПеремешивание колоды!!!\n";
        }
        ++i;
        return cards[i-1];
    }
};

class Chips{
    map<size_t, size_t> chips;
    size_t balance;
    void norm(){
        balance = 0;
        for(auto para : chips){
            balance += para.first*para.second;
            if(para.second == 0){
                chips.erase(chips[para.first]);
            }
        }
    }
    
public:
    Chips(const map<size_t, size_t>& EnChips = {}): chips(EnChips) {norm();}

    map<size_t, size_t> GetChips() const{
        return chips;
    }

    size_t GetBalance() const{
        return balance;
    }

    size_t SummChips(const Chips& chips_other){
        int sum = 0;
        for(auto para : chips_other.GetChips()){
            sum += para.first*para.second;
        }
        return sum;
    }

    friend ostream& operator << (ostream& out, const Chips& a){
        out << "Общий баланс: " << a.GetBalance();
        for(const auto& chip : a.GetChips()){
            out << " '" << chip.first << "' - " << chip.second << "шт.";
        }
        return out;
    } 

    friend istream& operator >> (istream& in, Chips& a){
        cout << "\nВводите номинал фишки, после количество. В конце введите 0:\n";
        size_t nom, kolvo;
        cin >> nom;
        map<size_t, size_t> EnChips;
        while(nom != 0){
            cin >> kolvo;
            EnChips[nom] += kolvo;
            cin >> nom;
        }
        a = Chips(EnChips);
        return in;
    }

    void BuyBalance(){
        cout << "Сколько фишек вы желаете приобрести\n";
        cin >> *this;
        norm();
    }

    void profit(const Chips& prof){
        for(const auto& para : prof.GetChips()){
            chips[para.first] += para.second;
        }
        norm();
    }

    void decline(const Chips& dec){
    norm();
    balance -= SummChips(dec);
    chips.clear();
    size_t mnoj = balance / 1000 + 1;
    chips[50*mnoj] = round((balance * 0.3)/(50*mnoj));
    size_t PromBal = balance - SummChips(chips);
    chips[20*mnoj] = round((PromBal * 0.4)/(20*mnoj));
    PromBal = balance - SummChips(chips);
    chips[10*mnoj] = round((PromBal * 0.5)/(10*mnoj));
    PromBal = balance - SummChips(chips);
    chips[5*mnoj] = round((PromBal * 0.9)/(5*mnoj));
    PromBal = balance - SummChips(chips);
    chips[1] = PromBal;
    norm();
    }

    bool ChipsReserve(const Chips& chips_other) const{
        size_t balance_other = 0;
        for(const auto& para : chips_other.GetChips()){
            balance_other += para.first*para.second;
        }
        return balance - balance_other > 0;
    }
};

Chips operator*(long long other, const Chips& a){
    Chips res;
    for(size_t i = 0; i < other; ++i){
        res.profit(a);
    }
    return res;
}

class Player{  
    Chips chips;
public:
    string name;
    Player(const string& na, const Chips& ba = Chips()): name(na), chips(ba){}
    
    map<size_t, size_t> GetChipsPlayer(){
        return chips.GetChips();
    }
    void profit(const Chips& prof){
        chips.profit(prof);
    }
    void decline(const Chips& dec){
        chips.decline(dec);
    }

    pair<Chips, size_t> DoBet(){
        Chips bet;
        size_t kolvo;
        do{
            do{
                cout << chips << "В сколько рук вы желаете играть(макс. 6)?\n";
                cin >> kolvo;
            }while(kolvo < 1 || kolvo > 6);
            cin >> bet;
            if(!chips.ChipsReserve(kolvo*bet)){
                cout << "Недостаточно средств\n";
            }
        }while(!chips.ChipsReserve(kolvo*bet));
        chips.decline(bet);
        return {bet, kolvo};
    }
};

class BlackJeck{
    deck cards;
    Player* player;
    deck CardsDiler;
    vector<pair<deck, Chips>> CardsPlayer;
public:
    BlackJeck(Player* pl): player(pl){cards.deck_52_Rand(8, 0.7);}

    size_t GetKolvoCards() const{
        return cards.GetKolvoCards();
    }
    size_t GetKolvoCardsInBita() const{
        return cards.GetKolvoCardsInBita();
    }

    vector<pair<deck, Chips>> GetCardsPlayer() const{
        return CardsPlayer;
    }
    
    void PlayBlackjack(){
        size_t KolvoHand;
        CardsDiler.DeckClear(); CardsPlayer.clear();
        cout << "Ваши ставки(глаз мой радуют всегда), " << player->name << ",(ставка на все руки одинакова)\n";
        auto para = player->DoBet();
        for(size_t i = 0; i < para.second; ++i){
            CardsPlayer.push_back({deck({cards.GetCard(), cards.GetCard()}), para.first});
        }
        CardsDiler = deck({cards.GetCard(), cards.GetCard()});
    }
};

ostream& operator << (ostream& out, const BlackJeck& a){
    out << "\nКарт в колоде осталось: " << a.GetKolvoCards() << "\nКарт в бите: " << a.GetKolvoCardsInBita()
        << "\nКарт до перемешивания колоды: " << 291 - a.GetKolvoCards() << "\n";
    
    return out;
} 

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    Player igrok = Player("Евгений");
    BlackJeck bleckjeck = BlackJeck(&igrok);

    system("pause");
    return 0;
}