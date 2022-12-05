// Class definition for XO_GameManager class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1

#include <iostream>
#include"XO_Classes.hpp"

using namespace std;

void GameManager::run() {
    Board x_o;
    int x, y, choice;
    Player *players[2];
    players[0] = new Player(1, 'X');
    cout << "Press 1 if you want to play with computer: ";
    cin >> choice;
    if (choice != 1)
        players[1] = new Player(2, 'O');
    else
        //Player pointer points to child
        players[1] = new ComputerPlayer ('O',x_o);

    x_o.display_board();
    while (true) {
        for (int i: {0, 1}) {
            players[i]->get_move(x, y);
            while (!x_o.update_board(x, y, players[i]->get_symbol())) {
                players[i]->get_move(x, y);
            }
            x_o.display_board();
            if (x_o.is_winner()) {
                cout << players[i]->to_string() << " wins\n";

                delete players[0];
                delete players[1];

                return;
            }
            if (x_o.is_draw()) {
                cout << "Draw!\n";
                delete players[0];
                delete players[1];
                return;
            }
        }
    }
}
