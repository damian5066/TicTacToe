#include "Board.hpp"
#include "Colors.hpp"
#include <iostream>

using namespace std;

// Wypelnia siatke spacjami - puste pole
Board::Board(int size, int winLength)
    : size(size), winLength(winLength)
{
    grid.assign(size, vector<char>(size, ' '));
}

// Getter rozmiaru
int Board::getSize()      const { return size; }

// Getter dlugosci wygranej
int Board::getWinLength() const { return winLength; }

// Pole jest puste jesli zawiera spacje
bool Board::isEmpty(int row, int col) const {
    return grid[row][col] == ' ';
}

// Stawia symbol - sprawdza granice i czy pole wolne
bool Board::setCell(int row, int col, char symbol) {
    if (row < 0 || row >= size || col < 0 || col >= size) return false;
    if (!isEmpty(row, col)) return false;
    grid[row][col] = symbol;
    return true;
}

// Przywraca pole do stanu pustego
void Board::clearCell(int row, int col) {
    grid[row][col] = ' ';
}

// Szuka pierwszego pustego pola - jesli nie znajdzie to plansza zapelniona
bool Board::isFull() const {
    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            if (grid[r][c] == ' ') return false;
    return true;
}

// Sprawdza wygrana we wszystkich kierunkach: poziom, pion, dwie skosne
bool Board::checkWin(char symbol) const {
    // poziomo
    for (int r = 0; r < size; r++)
        for (int c = 0; c <= size - winLength; c++) {
            bool win = true;
            for (int k = 0; k < winLength; k++)
                if (grid[r][c + k] != symbol) { win = false; break; }
            if (win) return true;
        }
    // pionowo
    for (int c = 0; c < size; c++)
        for (int r = 0; r <= size - winLength; r++) {
            bool win = true;
            for (int k = 0; k < winLength; k++)
                if (grid[r + k][c] != symbol) { win = false; break; }
            if (win) return true;
        }
    // skos w prawo
    for (int r = 0; r <= size - winLength; r++)
        for (int c = 0; c <= size - winLength; c++) {
            bool win = true;
            for (int k = 0; k < winLength; k++)
                if (grid[r + k][c + k] != symbol) { win = false; break; }
            if (win) return true;
        }
    // skos w lewo
    for (int r = 0; r <= size - winLength; r++)
        for (int c = winLength - 1; c < size; c++) {
            bool win = true;
            for (int k = 0; k < winLength; k++)
                if (grid[r + k][c - k] != symbol) { win = false; break; }
            if (win) return true;
        }
    return false;
}

// Rysuje plansze z numerami wierszy i kolumn oraz kolorami ANSI
void Board::draw() const {
    cout << "\n";
    cout << "    ";
    for (int c = 0; c < size; c++)
        cout << CYAN << BOLD << " " << c + 1 << "  ";
    cout << RESET << "\n";

    for (int r = 0; r < size; r++) {
        cout << "   ";
        for (int c = 0; c < size; c++) cout << "+---";
        cout << "+\n";

        cout << CYAN << BOLD << " " << r + 1 << " " << RESET;
        for (int c = 0; c < size; c++) {
            cout << "|";
            char cell = grid[r][c];
            if (cell == 'X') cout << RED << BOLD << " X " << RESET;
            else if (cell == 'O') cout << BLUE << BOLD << " O " << RESET;
            else                  cout << "   ";
        }
        cout << "|\n";
    }
    cout << "   ";
    for (int c = 0; c < size; c++) cout << "+---";
    cout << "+\n\n";
}
