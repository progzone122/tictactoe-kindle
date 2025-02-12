#include <iostream>
#include <config.hpp>

using namespace std;

class TicTacToe {
public:
    TicTacToe() : currentPlayer(1), currentMarker('X') {
        reset();
    }

    bool placeMarker(int slot) {
        int row = (slot - 1) / 3;
        int col = (slot - 1) % 3;

        if (grid[row][col] == 'X' || grid[row][col] == 'O') {
            if (DEBUG) {
                cout << "[DEBUG] This slot is already occupied! Try again." << endl;
            }
            return false;
        }

        grid[row][col] = currentMarker;

        if (DEBUG) {
            cout << "[DEBUG]" << " Marker " << currentMarker << " is inserted into slot " << slot << endl;
            cout << "[DEBUG]" << " Grid:" << endl;
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    cout << grid[row][col] << " ";
                }
                cout << endl;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        currentMarker = (currentMarker == 'X') ? 'O' : 'X';

        if (DEBUG) {
            cout << "[DEBUG]" << " Player switched to " << currentPlayer << endl;
            cout << "[DEBUG]" << " Marker switched to " << currentMarker << endl;
        }
    }

    void reset() {
        char num = ' ';
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                grid[row][col] = num;
            }
        }

        if (DEBUG) {
            cout << "[DEBUG]" << " Reset grid was successful" << endl;
        }
    }

    // there is a winner: 1 / 2
    // there is no winner: 0
    int checkWinner() {
        for (int i = 0; i < 3; ++i) {
            if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ') {
                return (grid[i][0] == 'X') ? 1 : 2;
            }
        }

        // rows / columns
        for (int i = 0; i < 3; ++i) {
            if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ') {
                return (grid[0][i] == 'X') ? 1 : 2;
            }
        }

        // diagonals
        if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ') {
            return (grid[0][0] == 'X') ? 1 : 2;
        }

        if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ') {
            return (grid[0][2] == 'X') ? 1 : 2;
        }
        return 0;
    }

    const char (&getGrid() const)[3][3] { return grid; }
    int getCurrentPlayer() const { return currentPlayer; }
    int getCurrentMarker() const { return currentMarker; }
private:
    char grid[3][3];
    int currentPlayer;
    char currentMarker;
};