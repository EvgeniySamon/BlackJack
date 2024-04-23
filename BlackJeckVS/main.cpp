#include <windows.h>
#include <ctime>
#include "Deck.h"
#include "Player.h"
#include "BlackJeck.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(unsigned(time(0)));
    /* Черный = 0, Синий = 1, Зеленый = 2, Голубой = 3, Красный = 4, Пурпурный = 5, коричневый = 6,
    светло-серый = 7, темно-серый = 8, светло-синий = 9, светло-зеленый = 10, светло-голубой = 11,
    светло-красный = 12, светло-пурпурный = 13, Желтый = 14, белый = 15
    SetConsoleTextAttribute(hConsole, 15); */
    Player igrok = Player("Евгений");
    BlackJeck blackjeck = BlackJeck(&igrok);
    blackjeck.Game();

    system("pause");
    return 0;
}