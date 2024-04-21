#include <windows.h>
#include <ctime>
#include <Card.h>
#include<Func.h>
#include<Deck.h>
#include<Chips.h>
#include<Player.h>
#include<Blackjeck.h>

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void color(const unsigned short int a){
    SetConsoleTextAttribute(hConsole, a);
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    /* Черный = 0, Синий = 1, Зеленый = 2, Голубой = 3, Красный = 4, Пурпурный = 5, коричневый = 6,
    светло-серый = 7, темно-серый = 8, светло-синий = 9, светло-зеленый = 10, светло-голубой = 11,
    светло-красный = 12, светло-пурпурный = 13, Желтый = 14, белый = 15 */

    Player igrok = Player("Евгений", Chips({{100, 10}, {50, 5}, {10, 10}}));
    BlackJeck blackjeck = BlackJeck(&igrok);
    while(igrok.GetChipsPlayer().GetBalance() != 0){
        blackjeck.PlayBlackjack();
    }

    system("pause");
    return 0;
}