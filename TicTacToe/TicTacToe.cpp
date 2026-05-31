#include <iostream>
#include <limits>
#include <string>

#include "Colors.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Game.hpp"

using namespace std;

static int readIntMain(const string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail() || val < minVal || val > maxVal) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid value. Enter " << minVal << "-" << maxVal << ": " << RESET;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
    }
}

static bool askIfAI(const string& label) {
    cout << "\n" << label << ":\n";
    cout << "  1. Human\n";
    cout << "  2. Computer (AI - MinMax)\n";
    return readIntMain("Choice (1-2): ", 1, 2) == 2;
}

int main() {
    cout << YELLOW << BOLD;
    cout << "TIC-TAC-TOE\n";
    cout << RESET << "\n";

    bool playAgain = true;
    while (playAgain) {
        cout << BOLD << "Game Setup\n" << RESET;

        int size = readIntMain("Board size (3-6 for AI, up to 10 for PvP): ", 3, 10);
        int winLen = readIntMain(
            "Win length (3-" + to_string(size) + "): ", 3, size);

        string name1;
        cout << "\nPlayer 1 name " << RED << "(X)" << RESET << ": ";
        getline(cin, name1);
        if (name1.empty()) name1 = "Player 1";
        bool ai1 = askIfAI("Player 1 (" + name1 + ")");

        string name2;
        cout << "\nPlayer 2 name " << BLUE << "(O)" << RESET << ": ";
        getline(cin, name2);
        if (name2.empty()) name2 = "Player 2";
        bool ai2 = askIfAI("Player 2 (" + name2 + ")");

        cout << "\n";
        Game game(size, winLen, name1, ai1, name2, ai2);
        game.run();

        cout << "\nPlay again? (y/n): ";
        char c; cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        playAgain = (c == 'y' || c == 'Y');
    }

    cout << CYAN << "\nGoodbye!\n" << RESET;
    return 0;
}
