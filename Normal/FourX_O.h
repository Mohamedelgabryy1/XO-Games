//
// Created by Lenovo on 11/29/2024.
//

#ifndef FOURX_O_H
#define FOURX_O_H

#include "BoardGame_Classes.h"

template <typename T>
class FourX_O_Board:public Board<T> {
public:
    FourX_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class FourX_O_Player : public Player<T> {
public:
    FourX_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

private:
    int from_x,from_y,to_x,to_y;
};

template <typename T>
class FourX_O_Random_Player : public RandomPlayer<T>{
public:
    FourX_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;

private:
    int from_x,from_y,to_x,to_y;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
FourX_O_Board<T>::FourX_O_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];

    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if (i == 0) {
                this->board[i][j] = (j % 2 == 0) ? 'X' : 'O';
            } else if (i == this->rows - 1) {
                this->board[i][j] = (j % 2 == 0) ? 'O' : 'X';
            } else {
                this->board[i][j] = 0;
            }
        }
    }
}



template <typename T>
bool FourX_O_Board<T>::update_board(int x, int y, T mark) {
    int from_x = x / 100, from_y = y / 100;
    int to_x = x % 100, to_y = y % 100;

    // Check bounds
    if (from_x < 0 || from_x >= this->rows || from_y < 0 || from_y >= this->columns ||
        to_x < 0 || to_x >= this->rows || to_y < 0 || to_y >= this->columns) {
        return false;
        }

    // Check if the move is valid
    if (this->board[from_x][from_y] == mark &&
        this->board[to_x][to_y] == 0 &&
        (from_x == to_x || from_y == to_y)) {

        this->board[from_x][from_y] = 0;
        this->board[to_x][to_y] = toupper(mark);
        return true;
        }

    return false;
}

// Display the board and the pieces on it
template <typename T>
void FourX_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool FourX_O_Board<T>::is_win() {
    // Check rows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= 1; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2]) {
                return true;
                }
        }
    }

    // Check columns
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i <= 1; i++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j]) {
                return true;
                }
        }
    }

    // Check diagonals
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            // Top-left to bottom-right
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2]) {
                return true;
                }
            // Top-right to bottom-left
            if (this->board[i][j + 2] != 0 &&
                this->board[i][j + 2] == this->board[i + 1][j + 1] &&
                this->board[i][j + 2] == this->board[i + 2][j]) {
                return true;
                }
        }
    }

    return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool FourX_O_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool FourX_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for FourX_O_Player
template <typename T>
FourX_O_Player<T>::FourX_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FourX_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease select the symbol of your move, x and y (0 to 3) separated by spaces: ";
    cin >> from_x >> from_y;
    cout<<"\nPlease enter the position you want to move it to , x and y (0 to 3) separated by spaces: ";
    cin>>to_x>>to_y;
    x=from_x*100+to_x;
    y=from_y*100+to_y;
}

// Constructor for FourX_O_Random_Player
template <typename T>
FourX_O_Random_Player<T>::FourX_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void FourX_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 3
    y = rand() % this->dimension;
}

#endif //FOURX_O_H
