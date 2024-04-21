#include<Player.h>

Chips Player::GetChipsPlayer(){
    return chips;
}

void Player::profit(const Chips& prof){
    chips.profit(prof);
}

void Player::decline(const Chips& dec){
    chips.decline(dec);
}

pair<Chips, size_t> Player::DoBet(){
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