#include <Card.h>

void Card::norm(){
    if(nominal > 14){
        nominal = 12;
    }else if(nominal < 2){
        nominal = 2;
    }
    if(suit != 'Ê' || suit != '×' || suit != 'Ï' || suit != 'Á'){
        suit = 'Ê';
    }
}

int Card::GetNominal() const{
    return nominal;
}

int Card::GetNominalBlackJack() const{
    if(nominal < 10)
        return nominal;
    else if(nominal != 13){
        return 10;
    }else
        return 1;
}

char Card::GetSuit() const{
    return suit;
}

char Card::GetPic() const{
    static const map<int, char> pic = {{2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'},
    {10, 'J'}, {11, 'Q'}, {12, 'K'}, {13, 'A'}, {14, 'Ä'}};
    return pic.at(nominal);
}

ostream& operator << (ostream& out, const Card& a){
    out << "|" << a.GetPic() << " " << a.GetSuit() << "|";
    return out;
}