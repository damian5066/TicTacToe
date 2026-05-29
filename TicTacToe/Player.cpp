#include "Player.hpp"

using namespace std;

// Zapisuje imie, symbol i flage AI
Player::Player(const string& name, char symbol, bool isAI)
    : name(name), symbol(symbol), isAI(isAI)
{
}

// Zwraca imie
string Player::getName() const {
    return name;
}

// Zwraca symbol
char Player::getSymbol() const {
    return symbol;
}

// Zwraca czy gracz to AI
bool Player::getIsAI() const {
    return isAI;
}
