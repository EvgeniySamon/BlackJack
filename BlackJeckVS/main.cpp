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
    /* ������ = 0, ����� = 1, ������� = 2, ������� = 3, ������� = 4, ��������� = 5, ���������� = 6,
    ������-����� = 7, �����-����� = 8, ������-����� = 9, ������-������� = 10, ������-������� = 11,
    ������-������� = 12, ������-��������� = 13, ������ = 14, ����� = 15
    SetConsoleTextAttribute(hConsole, 15); */
    Player igrok = Player("�������");
    BlackJeck blackjeck = BlackJeck(&igrok);
    blackjeck.Game();

    system("pause");
    return 0;
}