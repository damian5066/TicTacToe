#pragma once

#include <string>


// Klasa reprezentujaca jednego gracza (czlowiek lub AI)
class Player {
private:
    std::string name;   // imie gracza
    char symbol;        // symbol: 'X' lub 'O'
    bool isAI;          // true = gracz sterowany przez komputer

public:
    // Konstruktor - domyslnie gracz to czlowiek (isAI = false)
    Player(const std::string& name, char symbol, bool isAI = false);

    // Zwraca imie gracza
    std::string getName() const;

    // Zwraca symbol gracza ('X' lub 'O')
    char getSymbol() const;

    // Zwraca true jesli to AI
    bool getIsAI() const;
};