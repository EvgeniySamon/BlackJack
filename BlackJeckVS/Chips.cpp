#include "Chips.h"

void Chips::norm() {
    balance = 0;
    for (auto para : chips) {
        balance += para.first * para.second;
        if (para.second == 0) {
            chips.erase(chips[para.first]);
        }
    }
}

map<size_t, size_t> Chips::GetChips() const {
    return chips;
}

size_t Chips::GetBalance() const {
    return balance;
}

size_t Chips::SummChips(const Chips& chips_other) {
    int sum = 0;
    for (auto para : chips_other.GetChips()) {
        sum += para.first * para.second;
    }
    return sum;
}

ostream& operator<< (ostream& out, const Chips& a) {
    out << "Общий баланс: " << a.GetBalance() << " : ";
    for (const auto& chip : a.GetChips()) {
        out << " '" << chip.first << "' - " << chip.second << "шт.";
    }
    return out;
}

istream& operator >> (istream& in, Chips& a) {
    cout << "\nВводите номинал фишки, после количество. В конце введите 0:\n";
    size_t nom, kolvo;
    cin >> nom;
    map<size_t, size_t> EnChips;
    while (nom != 0) {
        cin >> kolvo;
        EnChips[nom] += kolvo;
        cin >> nom;
    }
    a = Chips(EnChips);
    return in;
}

void Chips::BuyBalance() {
    cout << "Сколько фишек вы желаете приобрести\n";
    cin >> *this;
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
    chips[50 * mnoj] = round((balance * 0.3) / (50 * mnoj));
    size_t PromBal = balance - SummChips(chips);
    chips[20 * mnoj] = round((PromBal * 0.4) / (20 * mnoj));
    PromBal = balance - SummChips(chips);
    chips[10 * mnoj] = round((PromBal * 0.5) / (10 * mnoj));
    PromBal = balance - SummChips(chips);
    chips[5 * mnoj] = round((PromBal * 0.9) / (5 * mnoj));
    PromBal = balance - SummChips(chips);
    chips[1] = PromBal;
    norm();
}

bool Chips::ChipsReserve(const Chips& chips_other) const {
    size_t balance_other = 0;
    for (const auto& para : chips_other.GetChips()) {
        balance_other += para.first * para.second;
    }
    return balance - balance_other > 0;
}

Chips operator*(long long other, const Chips& a) {
    Chips res;
    for (size_t i = 0; i < other; ++i) {
        res.profit(a);
    }
    return res;
}