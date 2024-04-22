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

    Player igrok = Player("Евгений");
    BlackJeck blackjeck = BlackJeck(&igrok);
    blackjeck.Game();

    system("pause");
    return 0;
}