#include "Card.h"

void Card::norm() {
    if (nominal > 15) {
        nominal = 10;
    }
    else if (nominal < 2) {
        nominal = 2;
    }
    if (suit != 'Ê' && suit != '×' && suit != 'Ï' && suit != 'Á') {
        suit = 'Ê';
    }
}

int Card::GetNominal() const {
    return nominal;
}

int Card::GetNominalBlackJack() const {
    if (nominal <= 10)
        return nominal;
    else if (nominal != 14) {
        return 10;
    }
    else
        return 11;
}

char Card::GetSuit() const {
    return suit;
}

string Card::GetPic() const {
    static const map<int, string> pic = {{2, "2"}, {3, "3"}, {4, "4"}, {5, "5"}, {6, "6"}, {7, "7"}, {8, "8"}, {9, "9"},
    {10, "10"}, {11, "J"}, {12, "Q"}, {13, "K"}, {14, "A"}, {15, "W"} };
    return pic.at(nominal);
}

ostream& operator << (ostream& out, const Card& a) {
    out << "|" << a.GetPic() << " " << a.GetSuit() << "|";
    return out;
}