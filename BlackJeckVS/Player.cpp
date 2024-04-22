#include "Player.h"

Chips Player::GetChipsPlayer() {
    return chips;
}

void Player::profit(const Chips& prof) {
    chips.profit(prof);
}

void Player::decline(const Chips& dec) {
    chips.decline(dec);
}

pair<Chips, size_t> Player::DoBet() {
    Chips bet; 
    size_t kolvo;
    do {
        do {
            cout << chips << "\n�o ������� ��� �� ������� ������(����. 6): ";
            cin >> kolvo;
        } while (kolvo < 1 || kolvo > 6);
        
        cin >> bet;
        if (!chips.ChipsReserve(kolvo * bet) || bet.GetBalance() == 0){
            cout << "������������ ������� ��� ������ � 0\n";
        }
    } while (!chips.ChipsReserve(kolvo * bet) || bet.GetBalance() == 0);
    chips.decline(kolvo * bet);
    return { bet, kolvo };
}

void Player::BuyBalance() {
    cout << "������� ����� �� ������� ����������?\n";
    cin >> chips;
}