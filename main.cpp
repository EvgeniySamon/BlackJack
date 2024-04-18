#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void color(const unsigned short int a){
    SetConsoleTextAttribute(hConsole, a);
}

class card{
    int nominal;
    char suit;
public:
    card(int nom, char su): nominal(nom), suit(su){norm();}
    void norm(){
        if(nominal > 14){
            nominal = 12;
        }else if(nominal < 2){
            nominal = 2;
        }
        if(suit != '?' || suit != '?' || suit != '?' || suit != '?'){
            suit = '?';
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
        {10, 'J'}, {11, 'Q'}, {12, 'K'}, {13, 'A'}, {14, '?'}};
        return pic.at(nominal);
    }
};

class deck{
    vector<pair<card, size_t>> cards;


public:
    size_t mix;
    void deck_52(size_t QuantityDecks = 1){
        static const vector<pair<card, size_t>>cards_Blackjeck = {
        {card(2, '?'), QuantityDecks}, {card(2, '?'), QuantityDecks}, {card(2, '?'), QuantityDecks}, {card(2, '?'), QuantityDecks},
        {card(3, '?'), QuantityDecks}, {card(3, '?'), QuantityDecks}, {card(3, '?'), QuantityDecks}, {card(3, '?'), QuantityDecks},
        {card(4, '?'), QuantityDecks}, {card(4, '?'), QuantityDecks}, {card(4, '?'), QuantityDecks}, {card(4, '?'), QuantityDecks},
        {card(5, '?'), QuantityDecks}, {card(5, '?'), QuantityDecks}, {card(5, '?'), QuantityDecks}, {card(5, '?'), QuantityDecks},
        {card(6, '?'), QuantityDecks}, {card(6, '?'), QuantityDecks}, {card(6, '?'), QuantityDecks}, {card(6, '?'), QuantityDecks},
        {card(7, '?'), QuantityDecks}, {card(7, '?'), QuantityDecks}, {card(7, '?'), QuantityDecks}, {card(7, '?'), QuantityDecks},
        {card(8, '?'), QuantityDecks}, {card(8, '?'), QuantityDecks}, {card(8, '?'), QuantityDecks}, {card(8, '?'), QuantityDecks},
        {card(9, '?'), QuantityDecks}, {card(9, '?'), QuantityDecks}, {card(9, '?'), QuantityDecks}, {card(9, '?'), QuantityDecks},
        {card(10, '?'), QuantityDecks}, {card(10, '?'), QuantityDecks}, {card(10, '?'), QuantityDecks}, {card(10, '?'), QuantityDecks},
        {card(11, '?'), QuantityDecks}, {card(11, '?'), QuantityDecks}, {card(11, '?'), QuantityDecks}, {card(11, '?'), QuantityDecks},
        {card(13, '?'), QuantityDecks}, {card(13, '?'), QuantityDecks}, {card(13, '?'), QuantityDecks}, {card(13, '?'), QuantityDecks},
        {card(12, '?'), QuantityDecks}, {card(12, '?'), QuantityDecks}, {card(12, '?'), QuantityDecks}, {card(12, '?'), QuantityDecks}
        };
        cards = cards_Blackjeck; mix = 230;
    }
    card GetRandCardForBlackjeck(){
        if(mix == 0){
            deck_52(8);
        }
        size_t i = rand() % 48 + rand() % 2;
        while(cards[i].second == 0){
            i = rand() % 48 + rand() % 2;
        }
        --cards[i].second;
        return cards[i].first;
    }
};

class Chips{
    map<size_t, size_t> chips;
    size_t balance;
    void norm(){
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
    size_t SummChips(const map<size_t, size_t>& chips_other){
        int sum = 0;
        for(auto para : chips_other){
            sum += para.first*para.second;
        }
        return sum;
    }
    friend ostream& operator << (ostream& out, const Chips& a){
    out << "Общий баланс:" << a.GetBalance();
    for(const auto& chip : a.GetChips()){
        out << "\t'" << chip.first << "' - " << chip.second << "шт.";
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
        for(auto para : prof.GetChips()){
            chips[para.first] += para.second;
        }
        norm();
    }
    void decline(const Chips& dec){
        for(const auto& para : dec.GetChips()){
            chips[para.first] -= para.second;
        }
        norm();
    }
    bool ChipsReserve(const Chips& chips_other){
        size_t balance_other = 0;
        for(const auto& para : chips_other.GetChips()){
            balance_other += para.first*para.second;
        }
        return balance - balance_other > 0;
    }
};



class Player{
    string name;
    Chips chips;
public:
    Player(const string& na, const Chips& ba): name(na), chips(ba){}
    
    map<size_t, size_t> GetChipsPlayer(){
        return chips.GetChips();
    }

    Chips DoBet(){
        Chips bet;
        do{
            cout << chips;
            cin >> bet;
        }while(!chips.ChipsReserve(bet));
        return bet;
    }
};

class BlackJeck{
    deck cards;
    Player& player;
    BlackJeck(Player& pl): player(pl){}
    vector<card> CardsDiler, CardsPlayer;
    map<size_t, size_t> bet;
    void PlayBlackjack(){
        CardsDiler.clear(); CardsPlayer.clear();
        cout << "Ваши ставки господа(глаз мой радуют всегда)";
        
    }
};

ostream& operator << (ostream& out, const BlackJeck& a){
    out << "////////";
    return out;
} 

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    system("pause");
    return 0;
}