// Class definition for XO_RandomPlayer class
// Which is a computer player playing randomly
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#include<iostream>
#include <vector>
#include"XO_Classes.hpp"

using namespace std;

// Set player symbol and name as Random Computer Player
ComputerPlayer::ComputerPlayer(char symbol, Board &board) : Player(symbol), board(board) {
    this->name = "Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void ComputerPlayer::get_move(int &x, int &y) {
    //play to block on player 1 and win computer without random
    best_move(x, y);
}

void ComputerPlayer::best_move(int &x, int &y) {
    Board copy_board = board;

    vector<pair<int, int>> empty_cells;
    int best_score = -1000;
    int score;
    int best_x, best_y;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (copy_board.update_board(i, j, symbol)) {
                empty_cells.emplace_back(i, j);
            }
        }
    }
    copy_board = board;
    for (auto cell: empty_cells) {
        copy_board.update_board(cell.first, cell.second, symbol);
        score = minimax(copy_board, 0);
        if (score > best_score || copy_board.is_winner()) {
            best_score = score;
            best_x = cell.first;
            best_y = cell.second;
        }
        copy_board = board;
    }
    cout << endl;
    x = best_x;
    y = best_y;

}

int ComputerPlayer::minimax(Board board1, bool isMax) {
    if (board1.is_winner()) {
        if (isMax) {
            return -1;
        } else {
            return 1;
        }
    }

    if (board1.is_draw()) {
        return 0;
    }
    Board copy_board = board1;
    int best_score;
    if (isMax) {
        best_score = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (copy_board.update_board(i, j, symbol)) {
                    best_score = max(best_score, minimax(copy_board, !isMax));
                    copy_board = board1;
                }
            }
        }
    } else {
        best_score = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (copy_board.update_board(i, j, 'X')) {
                    best_score = min(best_score, minimax(copy_board, !isMax));
                    copy_board = board1;
                }
            }
        }
    }
    return best_score;

}