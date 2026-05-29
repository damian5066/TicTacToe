#pragma once

#include <vector>

// Klasa reprezentujaca plansze gry
class Board {
private:
    int size;
    int winLength;
    std::vector<std::vector<char>> grid;

public:
    // Konstruktor - tworzy plansze size x size
    Board(int size, int winLength);

    // Zwraca rozmiar planszy
    int getSize() const;

    // Zwraca wymagana dlugosc do wygranej
    int getWinLength() const;

    // Sprawdza czy dane pole jest puste
    bool isEmpty(int row, int col) const;

    // Stawia symbol na polu; zwraca false jesli pole zajete lub poza plansza
    bool setCell(int row, int col, char symbol);

    // Czyści pole (uzywane przez MinMax do cofania ruchow)
    void clearCell(int row, int col);

    // Zwraca true jesli plansza jest pelna (remis)
    bool isFull() const;

    // Sprawdza czy dany symbol wygral
    bool checkWin(char symbol) const;

    // Rysuje plansze na ekranie
    void draw() const;
};

