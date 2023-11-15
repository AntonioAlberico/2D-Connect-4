#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <iostream> 

enum Player { NONE = 0, RED, BLUE };

// Forward declare the board size constants
extern const int ROWS;    // Forward declaration for ROWS
extern const int COLUMNS; // Forward declaration for COLUMNS

// Forward declare the board variable
extern std::vector<std::vector<Player>> board; // Forward declaration for board

bool placeToken(int column, Player currentPlayer) {
    if (column < 1 || column > COLUMNS) {
        std::cout << "Column out of bounds. Try again." << std::endl;
        return false;
    }

    // Adjust the column to be zero-based for the array access
    column--;

    // Start checking from the bottom of the column (last row index)
    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][column] == NONE) {
            board[row][column] = currentPlayer;
            return true;
        }
    }

    // If we get here, the column is full
    std::cout << "Column is full. Try again." << std::endl;
    return false;
}

bool checkWin(Player player) {
    // Check horizontal
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS - 3; ++col) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return true;
            }
        }
    }

    // Check vertical
    for (int col = 0; col < COLUMNS; ++col) {
        for (int row = 0; row < ROWS - 3; ++row) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int row = 0; row < ROWS - 3; ++row) {
        for (int col = 0; col < COLUMNS - 3; ++col) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return true;
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (int row = 3; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS - 3; ++col) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return true;
            }
        }
    }

    return false;
}

bool isBoardFull() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            if (board[row][col] == NONE) {
                return false;  // If any cell is empty, the board is not full
            }
        }
    }
    return true;  // No cells are empty; the board is full
}

#endif // GAME_LOGIC_H