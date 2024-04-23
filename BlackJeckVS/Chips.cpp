#include "Chips.h"

void Chips::norm() {
    balance = 0;
    for (const auto& para : chips) {
        balance += para.first * para.second;
    }
}

map<size_t, size_t> Chips::GetChips() const {
    return chips;
}

size_t Chips::GetBalance() const {
    return balance;
}

size_t Chips::SummChips(const Chips& chips_other){
    size_t sum = 0;
    for (const auto& para : chips_other.GetChips()) {
        sum += para.first * para.second;
    }
    return sum;
}

ostream& operator<< (ostream& out, const Chips& a) {
    out << a.GetBalance() << ": ";
    for (const auto& chip : a.GetChips()) {
        out << " '" << chip.first << "' - " << chip.second << "шт.";
    }
    return out;
}

istream& operator>> (istream& in, Chips& a) {
    cout << "¬водите номинал фишки, после количество(в конце введите 0):\n";
    size_t nom, kolvo;
    cin >> nom;
    map<size_t, size_t> m = {};
    while(nom != 0){
        cin >> kolvo;
        if(kolvo != 0)
            m[nom] += kolvo;
        cin >> nom;
    }
    a = Chips(m);
    return in;
}

void Chips::BuyBalance() {
    cout << "—колько фишек вы желаете приобрести?\n";
    Chips a;
    cin >> a;
    *this = a;
    norm();
}

void Chips::profit(const Chips& prof) {
    for (const auto& para : prof.GetChips()) {
        chips[para.first] += para.second;
    }
    norm();
}

void Chips::decline(const Chips& dec) {
    norm();
    balance -= SummChips(dec);
    chips.clear();
    size_t mnoj = balance / 1000 + 1;
    chips[50 * mnoj] = size_t(round((balance * 0.3) / (50 * mnoj)));
    size_t PromBal = balance - SummChips(chips);
    chips[20 * mnoj] = size_t(round((PromBal * 0.4) / (20 * mnoj)));
    PromBal = balance - SummChips(chips);
    chips[10 * mnoj] = size_t(round((PromBal * 0.5) / (10 * mnoj)));
    PromBal = balance - SummChips(chips);
    chips[5 * mnoj] = size_t(round((PromBal * 0.9) / (5 * mnoj)));
    PromBal = balance - SummChips(chips);
    chips[1] = PromBal;
    norm();
}

bool Chips::ChipsReserve(const Chips& chips_other) const {
    return balance >= chips_other.balance;
}

Chips operator*(size_t other, const Chips& a) {
    Chips res = a;
    for (size_t i = 0; i < other-1; ++i){
        res.profit(a);
    }
    return res;
}