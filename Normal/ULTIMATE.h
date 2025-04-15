//
// Created by melta on 08/12/2024.
//

#ifndef XO_GAME_ULTIMATE_H
#define XO_GAME_ULTIMATE_H
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
template <typename T>
class ULT_X_O_Board:public Board<T> {
public:
    ULT_X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    void mini_win();
    bool game_is_over();
private:

    X_O_Board<char>* ult[9];
};

template <typename T>
class ULT_X_O_Player : public Player<T> {
public:
    ULT_X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class ULT_X_O_Random_Player : public RandomPlayer<T>{
public:
    ULT_X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for ULT_X_O_Board
template <typename T>
ULT_X_O_Board<T>::ULT_X_O_Board() {

    for(int i=0;i<9;i++)
        this->ult[i]=new X_O_Board<char>;
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
}

template <typename T>
bool ULT_X_O_Board<T>::update_board(int x, int y, T mark) {
    int main_x = x / 3;
    int main_y = y / 3;
    int local_x = x % 3;
    int local_y = y % 3;

    int sub_board_index = main_x * 3 + main_y;

    if (sub_board_index < 0 || sub_board_index >= 9) return false;
    if (ult[sub_board_index]->board[local_x][local_y] != 0) return false;

    bool success = ult[sub_board_index]->update_board(local_x, local_y, mark);
    if (success) {
        mini_win();
    }
    return success;
}


// Display the board and the pieces on it
template <typename T>
void ULT_X_O_Board<T>::display_board() {

    for (int i = 0; i < 9; i++) {
        cout << "\n| ";
        for (int j = 0; j < 9; j++) {
            int ix=i/3;
            int iy=j/3;
            cout << "(" << i << "," << j << ")";
            switch(ix){
                case 0 :
                    switch(iy){
                        case 0:
                            cout << setw(2) << this->ult[0]->board[i%3][j%3] << " |";
                            break;
                        case 1:
                            cout << setw(2) << this->ult[1]->board[i%3][j%3] << " |";
                            break;
                        case 2:
                            cout << setw(2) << this->ult[2]->board[i%3][j%3] << " |";
                            break;

                        default:break;
                    }
                    break;
                case 1:
                    switch(iy){
                        case 0:
                            cout << setw(2) << this->ult[3]->board[i%3][j%3] << " |";
                            break;
                        case 1:
                            cout << setw(2) << this->ult[4]->board[i%3][j%3] << " |";
                            break;
                        case 2:
                            cout << setw(2) << this->ult[5]->board[i%3][j%3] << " |";
                            break;

                        default:break;
                    }
                    break;
                case 2:
                    switch(iy){
                        case 0:
                            cout << setw(2) << this->ult[6]->board[i%3][j%3] << " |";
                            break;
                        case 1:
                            cout << setw(2) << this->ult[7]->board[i%3][j%3] << " |";
                            break;
                        case 2:
                            cout << setw(2) << this->ult[8]->board[i%3][j%3] << " |";
                            break;
                        default:break;
                    }
                    break;

                default:break;
            }

        }
        cout << "\n--------------------------------------------------------------------------";
    }
    cout << endl;
    cout<<"win board:"<<endl;
    for (int i = 0; i < 3; i++) {
        cout << "\n| ";
        for (int j = 0; j < 3; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;

}
template <typename T>
void ULT_X_O_Board<T>::mini_win() {
    for (int i = 0; i < 9; i++) {
        if (ult[i]->is_win() && this->board[i / 3][i % 3] == 0) {
            this->board[i / 3][i % 3] = ult[i]->mark; // Mark the winning sub-board
        }
    }
}

// Returns true if there is any winner
template <typename T>
bool ULT_X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool ULT_X_O_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool ULT_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for ULT_X_O_Player
template <typename T>
ULT_X_O_Player<T>::ULT_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ULT_X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for ULT_X_O_Random_Player
template <typename T>
ULT_X_O_Random_Player<T>::ULT_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ULT_X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif //XO_GAME_ULTIMATE_H
