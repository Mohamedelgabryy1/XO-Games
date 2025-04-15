//
// Created by momen on 11/29/2024.
//

#ifndef FOURINAROW_H
#define FOURINAROW_H
#include "BoardGame_Classes.h"
template <typename T>
class FourInARowBoard : public Board<T> {
public:
    FourInARowBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool check_horizontal();
    bool check_vertical();
    bool check_diagonal();
};

template <typename T>
class FourInARowPlayer: public Player<T> {
public:
    FourInARowPlayer(string name, T symbol);
    void getmove(int&x,int&y);
    void getmove(int& x, int& y, int& number);
};


template <typename T>
class FourInARow_Random_Player : public RandomPlayer<T>{
public:
    FourInARow_Random_Player (T symbol);
    void getmove(int&x,int&y);
    void getmove(int &x, int &y,int &n) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include<bits/stdc++.h>
using namespace std;

// Constructor for X_O_Board

template <typename T>
FourInARowBoard<T>::FourInARowBoard() {
    this->rows = 6;  // 6 rows
    this->columns = 7; // 7 columns
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
    }

    // Initialize the board to 0 (empty)
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}



template <typename T>
bool FourInARowBoard<T>::update_board(int x, int y, T symbol) {
    // Only column (y) is used, as we place marks in the lowest available square
    if (y < 0 || y >= this->columns) {
        return false; // Invalid column
    }

    for (int i = this->rows - 1; i >= 0; i--) { // Start from the bottom of the column
        if (this->board[i][y] == 0) {
            this->board[i][y] = symbol; // Place the symbol in the lowest empty square
            this->n_moves++;
            return true;
        }
    }

    return false; // Column is full
}

// Display the board and the pieces on it
template <typename T>
void FourInARowBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0)
                cout << "   |";
            else
                cout << " " << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
bool FourInARowBoard<T>::check_horizontal() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j+1] &&
                this->board[i][j] == this->board[i][j+2] &&
                this->board[i][j] == this->board[i][j+3]) {
                return true;
                }
        }
    }
    return false;
}
template <typename T>
bool FourInARowBoard<T>::check_vertical() {
    for (int i = 0; i <= this->rows - 4; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j] &&
                this->board[i][j] == this->board[i+2][j] &&
                this->board[i][j] == this->board[i+3][j]) {
                return true;
                }
        }
    }
    return false;
}
template <typename T>
bool FourInARowBoard<T>::check_diagonal() {
    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 4; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j+1] &&
                this->board[i][j] == this->board[i+2][j+2] &&
                this->board[i][j] == this->board[i+3][j+3]) {
                return true;
                }
        }
    }

    // Check diagonals (bottom-left to top-right)
    for (int i = 3; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i-1][j+1] &&
                this->board[i][j] == this->board[i-2][j+2] &&
                this->board[i][j] == this->board[i-3][j+3]) {
                return true;
                }
        }
    }

    return false;
}
// Returns true if there is any winner
template <typename T>
bool FourInARowBoard<T>::is_win() {
    return check_horizontal() || check_vertical() || check_diagonal();
}

// Return true if 9 moves are done and no winner
template <typename T>
bool FourInARowBoard<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool FourInARowBoard<T>::game_is_over() {
    return is_win() || is_draw();
}


//--------------------------------------

// Constructor for X_O_Player
template <typename T>
FourInARowPlayer<T>::FourInARowPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FourInARowPlayer<T>::getmove(int& x, int& y) {
    const int MIN_COLUMN = 0;
    const int MAX_COLUMN = 6;

    while (true) {
        cout << this->name << ", enter the column (0-6) to place your " << this->symbol << ": ";
        cin >> y;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input. Please enter a number between 0 and 6.\n";
            continue;
        }

        if (y < MIN_COLUMN || y > MAX_COLUMN) {
            cout << "Invalid column. Please enter a column between 0 and 6.\n";
            continue;
        }// Not used
        break;
    }
}



// Constructor for FourInARow_Random_Player
template <typename T>
FourInARow_Random_Player<T>::FourInARow_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}


template <typename T>
void FourInARow_Random_Player<T>::getmove(int& x, int& y) {
    const int MIN_NUM = 1;     // Minimum allowed number
    const int MAX_NUM = 9;     // Maximum allowed number

    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    // Random number between MIN_NUM and MAX_NUM
}
//---------------------------------
//Non-used classes from parent which need implementation
template <typename T>
void FourInARowPlayer<T>::getmove(int& x, int& y,int &n) {}
template <typename T>
void FourInARow_Random_Player<T>::getmove(int& x, int& y,int &n) {}
#endif //FOURINAROW_H
