#include <windows.h>
#include <ctime>
#include "Deck.h"
#include "Player.h"
#include "BlackJeck.h"

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void color(const unsigned short int a) {
    SetConsoleTextAttribute(hConsole, a);
}
// g++ -I/Blackjack/include main.cpp

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(unsigned(time(0)));
    /* ������ = 0, ����� = 1, ������� = 2, ������� = 3, ������� = 4, ��������� = 5, ���������� = 6,
    ������-����� = 7, �����-����� = 8, ������-����� = 9, ������-������� = 10, ������-������� = 11,
    ������-������� = 12, ������-��������� = 13, ������ = 14, ����� = 15 */

    Player igrok = Player("�������", Chips({ {100, 10}, {50, 5}, {10, 10} }));
    BlackJeck blackjeck = BlackJeck(&igrok);
    Deck deck;
    deck.deck_52_Rand(8);
    cout << deck << "\n";

    system("pause");
    return 0;
}