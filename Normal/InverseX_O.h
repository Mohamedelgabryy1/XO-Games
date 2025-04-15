//
// Created by Lenovo on 11/26/2024.
//

#ifndef INVERSEX_O_H
#define INVERSEX_O_H

#include "BoardGame_Classes.h"


template <typename T>
class InverseX_O_Board:public Board<T> {
public:
    InverseX_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

    static bool win;
    char mark;

};

template <typename T>
class InverseX_O_Player : public Player<T> {
public:
    InverseX_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class InverseX_O_Random_Player : public RandomPlayer<T>{
public:
    InverseX_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template<typename T>
bool InverseX_O_Board<T>::win=bool(false);

// Constructor for X_O_Board
template <typename T>
InverseX_O_Board<T>::InverseX_O_Board() {
    this->rows = this->columns = 3;

    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;

    if (this->n_moves==0)
    InverseX_O_Board<T>::win=false;
}

template <typename T>
bool InverseX_O_Board<T>::update_board(int x, int y, T mark) {
    this->mark = mark;

    if(InverseX_O_Board<T>::win)return true;

    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void InverseX_O_Board<T>::display_board() {
    if(InverseX_O_Board<T>::win)return;

    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool InverseX_O_Board<T>::is_win() {
    // Loop to check for standard rows, columns, and diagonals
    for (int i = 0; i < this->rows; i++) {
        // Check rows
        if (this->board[i][0] == this->board[i][1] &&
            this->board[i][1] == this->board[i][2] &&
            this->board[i][0] != 0) {
            this->win = true;
            if (this->mark!=this->board[i][0]) {
                return true;
            }
            }


        // Check columns
        if (this->board[0][i] == this->board[1][i] &&
            this->board[1][i] == this->board[2][i] &&
            this->board[0][i] != 0) {
            this->win = true;
            if (this->mark!=this->board[0][i]) {
                return true;
            }
            }
    }

    // Check diagonal top left to down right
    if (this->board[0][0] == this->board[1][1] &&
        this->board[1][1] == this->board[2][2] &&
        this->board[0][0] != 0) {
        this->win = true;
        if (this->mark!=this->board[0][0]) {
            return true;
        }
        }

    // Check diagonal top right to down left
    if (this->board[0][2] == this->board[1][1] &&
        this->board[1][1] == this->board[2][0] &&
        this->board[0][2] != 0) {
            this->win = true;
        if (this->mark!=this->board[0][2]) {
            return true;
        }
    }
    return false;
}



// Return true if 9 moves are done and no winner
template <typename T>
bool InverseX_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool InverseX_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
InverseX_O_Player<T>::InverseX_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void InverseX_O_Player<T>::getmove(int& x, int& y) {
    if (InverseX_O_Board<T>::win==true) {return;}

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
InverseX_O_Random_Player<T>::InverseX_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {

    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

}

template <typename T>
void InverseX_O_Random_Player<T>::getmove(int& x, int& y) {
    if (InverseX_O_Board<T>::win==true) {return;}

    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}




#endif //INVERSEX_O_H
