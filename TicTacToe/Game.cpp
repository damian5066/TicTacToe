#include "Game.hpp"
#include "Colors.hpp"
#include <iostream>
#include <limits>

using namespace std;

// Tworzy plansze i graczy na podstawie parametrow z main
Game::Game(int size, int winLen,
    const string& name1, bool ai1,
    const string& name2, bool ai2)
    : board(size, winLen),
    player1(name1, 'X', ai1),
    player2(name2, 'O', ai2),
    currentPlayer(0)
{
}

// Ocenia plansze po zakonczeniu gry
// Odejmujemy/dodajemy depth zeby AI wolalo szybsze wygrane
int Game::evaluate(char aiSymbol, char humanSymbol) const {
    if (board.checkWin(aiSymbol))    return  1000;
    if (board.checkWin(humanSymbol)) return -1000;
    return 0; // remis lub stan nierozstrzygnieny
}

// Glowna rekurencja MinMax z przycinaniem alfa-beta
// isMaximizing = true gdy tura AI (chce maksymalizowac wynik)
// alpha = najlepsze co MAX moze zagwarantowac
// beta  = najlepsze co MIN moze zagwarantowac
// Przycinamy galaz gdy beta <= alpha (przeciwnik nie wybierze tej sciezki)
int Game::minimax(int depth, bool isMaximizing,
    int alpha, int beta,
    char aiSymbol, char humanSymbol)
{
    // Sprawdzamy czy gra sie skonczyla lub osiagnelismy limit glebokosci
    int score = evaluate(aiSymbol, humanSymbol);
    if (score == 1000) return score - depth;
    if (score == -1000) return score + depth;
    if (board.isFull()) return 0;
    if (depth >= MAX_DEPTH) return 0;

    int size = board.getSize();

    if (isMaximizing) {
        // Tura AI - szukamy ruchu o NAJWIEKSZEJ wartosci
        int best = numeric_limits<int>::min();
        for (int r = 0; r < size && beta > alpha; r++) {
            for (int c = 0; c < size && beta > alpha; c++) {
                if (!board.isEmpty(r, c)) continue;

                board.setCell(r, c, aiSymbol);   // wykonaj ruch
                int val = minimax(depth + 1, false, alpha, beta,
                    aiSymbol, humanSymbol);
                board.clearCell(r, c);           // cofnij ruch

                if (val > best)  best = val;
                if (best > alpha) alpha = best;
            }
        }
        return best;
    }
    else {
        // Tura przeciwnika - szukamy ruchu o NAJMNIEJSZEJ wartosci
        int best = numeric_limits<int>::max();
        for (int r = 0; r < size && beta > alpha; r++) {
            for (int c = 0; c < size && beta > alpha; c++) {
                if (!board.isEmpty(r, c)) continue;

                board.setCell(r, c, humanSymbol); // wykonaj ruch
                int val = minimax(depth + 1, true, alpha, beta,
                    aiSymbol, humanSymbol);
                board.clearCell(r, c);            // cofnij ruch

                if (val < best) best = val;
                if (best < beta) beta = best;
            }
        }
        return best;
    }
}

// Iteruje po wszystkich pustych polach i wybiera to z najwyzszym wynikiem MinMax
void Game::findBestMove(char aiSymbol, char humanSymbol,
    int& bestRow, int& bestCol)
{
    int bestVal = numeric_limits<int>::min();
    bestRow = bestCol = -1;

    int size = board.getSize();
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (!board.isEmpty(r, c)) continue;

            board.setCell(r, c, aiSymbol);
            // Po ruchu AI nastepuje tura MIN (isMaximizing = false)
            int val = minimax(0, false,
                numeric_limits<int>::min(),
                numeric_limits<int>::max(),
                aiSymbol, humanSymbol);
            board.clearCell(r, c);

            if (val > bestVal) {
                bestVal = val;
                bestRow = r;
                bestCol = c;
            }
        }
    }
}

// Wczytuje liczbe z zakresu [minVal, maxVal], ponawia przy blednym wpisie
int Game::readInt(const string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail() || val < minVal || val > maxVal) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "  Error! Enter a number from "
                << minVal << " to " << maxVal << ".\n" << RESET;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
    }
}

// Zwraca referencje do gracza ktory teraz gra
Player& Game::getCurrentPlayer() {
    return (currentPlayer == 0) ? player1 : player2;
}

// Przelacza aktywnego gracza: 0->1 lub 1->0
void Game::switchPlayer() {
    currentPlayer = 1 - currentPlayer;
}

// Wyswietla ramke tytulowa
void Game::printHeader() const {
    cout << YELLOW << BOLD;
    cout << "TIC - TAC - TOE\n";
    cout << RESET;
}

// Glowna petla gry: rysuje plansze, pyta o ruch (lub pyta AI), sprawdza wynik
void Game::run() {
    printHeader();
    cout << GREEN << "Board: " << board.getSize() << "x" << board.getSize()
        << "  |  Win length: " << board.getWinLength() << "\n" << RESET;

    if (player1.getIsAI())
        cout << CYAN << "[AI] " << player1.getName() << " plays automatically.\n" << RESET;
    if (player2.getIsAI())
        cout << CYAN << "[AI] " << player2.getName() << " plays automatically.\n" << RESET;

    while (true) {
        board.draw();

        Player& current = getCurrentPlayer();
        char mySymbol = current.getSymbol();
        char otherSymbol = (mySymbol == 'X') ? 'O' : 'X';

        // Komunikat w kolorze aktualnego gracza
        if (mySymbol == 'X') cout << RED << BOLD;
        else                 cout << BLUE << BOLD;
        cout << current.getName() << " (" << mySymbol << ")" << RESET << " - your move!\n";

        int row, col;

        if (current.getIsAI()) {
            // AI oblicza najlepszy ruch
            cout << CYAN << "  [AI thinking...]\n" << RESET;
            findBestMove(mySymbol, otherSymbol, row, col);
            cout << "  AI plays: row " << row + 1 << ", col " << col + 1 << "\n";
            board.setCell(row, col, mySymbol);
        }
        else {
            // Czlowiek wpisuje wspolrzedne; ponawia jesli pole zajete
            while (true) {
                row = readInt("  Row    (1-" + to_string(board.getSize()) + "): ",
                    1, board.getSize()) - 1;
                col = readInt("  Column (1-" + to_string(board.getSize()) + "): ",
                    1, board.getSize()) - 1;
                if (board.setCell(row, col, mySymbol)) break;
                cout << RED << "  Cell taken! Try again.\n" << RESET;
            }
        }

        // Sprawdzamy czy ktos wygral lub jest remis
        if (board.checkWin(mySymbol)) {
            board.draw();
            cout << GREEN << BOLD
                << "*** Congratulations, " << current.getName()
                << " (" << mySymbol << ") wins! ***\n" << RESET;
            break;
        }

        if (board.isFull()) {
            board.draw();
            cout << YELLOW << BOLD << "Draw! Good game.\n" << RESET;
            break;
        }

        switchPlayer();
    }
}
