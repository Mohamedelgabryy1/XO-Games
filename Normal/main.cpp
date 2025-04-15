/*   FOUR IN A ROW, NUMERICAL,SUS HEADERS:
 *   Missing Identification ( Abstract using default X_O board and players)
 *
 *   Added system("CLS") to all headers except the three above and the Word because it didnt work in it
 *
 *   NUMERICAL doesn't have numbers on the cells of xo -> ex. |(0,0)|(0,1)|(0,2)|
 *
 *   If you have time run all games(I did so but just to make sure)
 */


#include <iostream>
#include <string>
#include <limits>
#include "BoardGame_Classes.h"
#include "PyramidX_O.h"
#include "FiveX_O.h"
#include "WordX_O.h"
#include "InverseX_O.h"
#include "FourX_O.h"
#include "FourInARow.h"
#include "NumericalX_O.h"
#include "ULTIMATE.h"
using namespace std;

int main() {
    string player1Name, player2Name;
    int choice, t1, t2;

    while (true) {
        Player<char>* players[2];
        Board<char>* B = nullptr;

        cout << "******** Select a Game ********\n";
        cout << "1. Pyramid Tic-Tac-Toe\n";
        cout << "2. Four-in-a-row\n";
        cout << "3. 5 x 5 Tic-Tac-Toe\n";
        cout << "4. Word Tic-Tac-Toe\n";
        cout << "5. Numerical Tic-Tac-Toe\n";
        cout << "6. Misere(Inverse) Tic-Tac-Toe\n";
        cout << "7. 4x4 Tic-Tac-Toe\n";
        cout << "8. ULTIMATE Tic-Tac-Toe\n";
        cout << "9. Exit\n";

        while (true) {
            cout << "Enter the game type: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 9) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number between " << 1 << " and " << 9 << ".\n";
            } else {
                system("CLS");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        if (choice == 10) {
            cout << "Thank you for playing!\n";
            break;
        }

        cout<<"Enter Player 1's Name: ";
        cin>>player1Name;

        while (true) {
            cout << "Choose Player 1's Type:\n1. Human\n2. Random Computer\n";
            cin >> t1;

            if (cin.fail() || t1 < 1 || t1 > 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter either " << 1 << " or " << 2 << ".\n";
            } else {
                system("CLS");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        cout<<"Enter Player 2's Name: ";
        cin>>player2Name;

        while (true) {
            cout << "Choose Player 1's Type:\n1. Human\n2. Random Computer\n";
            cin >> t2;

            if (cin.fail() || t2 < 1 || t2 > 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter either " << 1 << " or " << 2 << ".\n";
            } else {

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        switch (choice) {
            case 1: {
                B = new PyramidX_O_Board<char>();
                players[0] = (t1 == 1)
                ? static_cast<Player<char>*>(new PyramidX_0_Player<char>(player1Name, 'X'))
                : static_cast<Player<char>*>(new PyramidX_0_Random_Player<char>('X'));
                players[1] = (t2 == 1)
                ? static_cast<Player<char>*>(new PyramidX_0_Player<char>(player2Name, 'O'))
                : static_cast<Player<char>*>(new PyramidX_0_Random_Player<char>('O'));
                break;
            }
            case 2: {
                B = new FourInARowBoard<char>();
                players[0] = (t1 == 1)
                             ? static_cast<Player<char>*>(new FourInARowPlayer<char>(player1Name, 'X'))
                             : static_cast<Player<char>*>(new FourInARow_Random_Player<char>('X'));
                players[1] = (t2 == 1)
                             ? static_cast<Player<char>*>(new FourInARowPlayer<char>(player2Name, 'O'))
                             : static_cast<Player<char>*>(new FourInARow_Random_Player<char>('O'));
                break;
            }
            case 3: {
                B = new FiveX_O_Board<char>();
                players[0] = (t1 == 1)
                    ? static_cast<Player<char>*>(new FiveX_O_Player<char>(player1Name, 'X'))
                    : static_cast<Player<char>*>(new FiveX_O_Random_Player<char>('X'));
                players[1] = (t2 == 1)
                    ? static_cast<Player<char>*>(new FiveX_O_Player<char>(player2Name, 'O'))
                    : static_cast<Player<char>*>(new FiveX_O_Random_Player<char>('O'));
                break;
            }
            case 5: {
                B = new NumX_O_Board<char>();
                players[0] = (t1 == 1)
                             ? static_cast<Player<char>*>(new NumX_O_Player<char>(player1Name, 'X',0))
                             : static_cast<Player<char>*>(new NumX_O_Random_Player<char>('X'));
                players[1] = (t2 == 1)
                             ? static_cast<Player<char>*>(new NumX_O_Player<char>(player2Name, 'O',1))
                             : static_cast<Player<char>*>(new NumX_O_Random_Player<char>('O'));
                break;
            }
            case 4: {
                B = new WordX_O_Board<char>();
                players[0] = (t1 == 1)
                    ? static_cast<Player<char>*>(new WordX_O_Player<char>(player1Name, 'X'))
                    : static_cast<Player<char>*>(new WordX_O_Random_Player<char>('X'));
                players[1] = (t2 == 1)
                    ? static_cast<Player<char>*>(new WordX_O_Player<char>(player2Name, 'O'))
                    : static_cast<Player<char>*>(new WordX_O_Random_Player<char>('O'));
                break;
            }
            case 6: {
                B = new InverseX_O_Board<char>();
                players[0] = (t1 == 1)
                ? static_cast<Player<char>*>(new InverseX_O_Player<char>(player1Name, 'X'))
                : static_cast<Player<char>*>(new InverseX_O_Random_Player<char>('X'));
                players[1] = (t2 == 1)
                ? static_cast<Player<char>*>(new InverseX_O_Player<char>(player2Name, 'O'))
                : static_cast<Player<char>*>(new InverseX_O_Random_Player<char>('O'));
                break;
            }
                case 7: {
                    B = new FourX_O_Board<char>();
                    players[0] = (t1 == 1)
                    ? static_cast<Player<char>*>(new FourX_O_Player<char>(player1Name, 'X'))
                    : static_cast<Player<char>*>(new FourX_O_Random_Player<char>('X'));
                    players[1] = (t2 == 1)
                    ? static_cast<Player<char>*>(new FourX_O_Player<char>(player2Name, 'O'))
                    : static_cast<Player<char>*>(new FourX_O_Random_Player<char>('O'));
                    break;
                }
                case 8: {
                    B = new ULT_X_O_Board<char>();
                    players[0] = (t1 == 1)
                                 ? static_cast<Player<char>*>(new ULT_X_O_Player<char>(player1Name, 'X'))
                                 : static_cast<Player<char>*>(new ULT_X_O_Random_Player<char>('X'));
                    players[1] = (t2 == 1)
                                 ? static_cast<Player<char>*>(new ULT_X_O_Player<char>(player1Name, 'O'))
                                 : static_cast<Player<char>*>(new ULT_X_O_Random_Player<char>('O'));
                    break;
                }

                default: {
                 break;
            }
}

        GameManager<char> game(B, players);
        game.run();


        // Clean up for restart
        delete B;
        for (auto& player : players) {
            delete player;
        }
    }

    return 0;
}
