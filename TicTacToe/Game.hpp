#pragma once

#include <string>
#include "Board.hpp"
#include "Player.hpp"

// Klasa zarzadzajaca przebiegiem gry
class Game {
private:
    Board board;
    Player player1;
    Player player2;
    int currentPlayer; // 0 = gracz1, 1 = gracz2

    // Maksymalna glebokosc przeszukiwania drzewa MinMax
    static const int MAX_DEPTH = 6;

    // Ocenia stan planszy: +1000 wygrana AI, -1000 przegrana, 0 remis
    int evaluate(char aiSymbol, char humanSymbol) const;

    // Rekurencyjny algorytm MinMax z przycinaniem alfa-beta
    int minimax(int depth, bool isMaximizing,
        int alpha, int beta,
        char aiSymbol, char humanSymbol);

    // Szuka najlepszego ruchu dla AI i zapisuje go do bestRow/bestCol
    void findBestMove(char aiSymbol, char humanSymbol,
        int& bestRow, int& bestCol);

    // Wczytuje liczbe z klawiatury z walidacja zakresu
    int readInt(const std::string& prompt, int minVal, int maxVal);

    // Zwraca referencje do aktualnego gracza
    Player& getCurrentPlayer();

    // Zmienia aktywnego gracza (0->1 lub 1->0)
    void switchPlayer();

    // Wyswietla naglowek gry
    void printHeader() const;

public:
    // Konstruktor - tworzy plansze i obu graczy
    Game(int size, int winLen,
        const std::string& name1, bool ai1,
        const std::string& name2, bool ai2);

    // Uruchamia glowna petle gry
    void run();
};
