#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;
    int scoreX, scoreO;

public:
    TicTacToe() {
        resetBoard();
        currentPlayer = 'X';
        scoreX = 0;
        scoreO = 0;
    }

    void resetBoard() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
    }

    void displayBoard() {
        clearScreen();
        cout << "\n  TIC TAC TOE\n\n";
        for (int i = 0; i < 3; i++) {
            cout << "   " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
            if (i < 2) cout << "  ---|---|---\n";
        }
        cout << "\n  Score -> X: " << scoreX << "   O: " << scoreO << "\n\n";
    }

    bool isValidMove(int row, int col) {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
    }

    void makeMove(int row, int col) {
        board[row][col] = currentPlayer;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    char getCurrentPlayer() {
        return currentPlayer;
    }

    bool checkWin() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return true;
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return true;
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return true;
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return true;
        return false;
    }

    bool checkDraw() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                    return false;
        return true;
    }

    void updateScore(char winner) {
        if (winner == 'X') scoreX++;
        else if (winner == 'O') scoreO++;
    }

    void play() {
        bool gameOver = false;
        int row, col;

        while (!gameOver) {
            displayBoard();
            cout << "  Player " << currentPlayer << "'s turn\n";
            cout << "  Enter row and column (1-3 1-3): ";

            if (!(cin >> row >> col)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Invalid input, press enter to continue...";
                cin.get();
                continue;
            }

            row--;
            col--;

            if (!isValidMove(row, col)) {
                cout << "  Invalid move, press enter to continue...";
                cin.ignore();
                cin.get();
                continue;
            }

            makeMove(row, col);

            if (checkWin()) {
                updateScore(currentPlayer);
                displayBoard();
                cout << "  Player " << currentPlayer << " wins the round!\n";
                gameOver = true;
            } else if (checkDraw()) {
                displayBoard();
                cout << "  It's a draw!\n";
                gameOver = true;
            } else {
                switchPlayer();
            }
        }

        cout << "\n  Press enter to continue...";
        cin.ignore();
        cin.get();
    }
};

int main() {
    TicTacToe game;
    char playAgain;

    do {
        game.play();
        cout << "  Play again? (y/n): ";
        cin >> playAgain;
        game.resetBoard();
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\n  Thanks for playing!\n";
    return 0;
}