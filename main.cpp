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
    /* ������ = 0, ����� = 1, ������� = 2, ������� = 3, ������� = 4, ��������� = 5, ���������� = 6,
    ������-����� = 7, �����-����� = 8, ������-����� = 9, ������-������� = 10, ������-������� = 11,
    ������-������� = 12, ������-��������� = 13, ������ = 14, ����� = 15 */

    Player igrok = Player("�������", Chips({{100, 10}, {50, 5}, {10, 10}}));
    BlackJeck blackjeck = BlackJeck(&igrok);
    while(igrok.GetChipsPlayer().GetBalance() != 0){
        blackjeck.PlayBlackjack();
    }

    system("pause");
    return 0;
}