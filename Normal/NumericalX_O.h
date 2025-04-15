#ifndef _NumericalX_O_H
#define _NumericalX_O_H

#include "BoardGame_Classes.h"
template <typename T>
class NumX_O_Board:public Board<T> {
public:
    NumX_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool check_sum(int a, int b, int c);
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class NumX_O_Player : public Player<T> {
public:
    NumX_O_Player(string name, T symbol, bool isOdd);
    void getmove(int& x, int& y, int& number);
    void getmove(int& x, int& y);
    bool isNumberChosen(T number);
private:
    bool isOdd; // Player type: odd or even numbers
    vector<T> chosenNumbers;
};
template <typename T>
NumX_O_Player<T>::NumX_O_Player(string name, T symbol, bool isOdd)
    : Player<T>(name, symbol), isOdd(isOdd) {}

template <typename T>
bool NumX_O_Player<T>::isNumberChosen(T number) {
    for (int i = 0; i < chosenNumbers.size(); i++) {
        if (chosenNumbers[i] == number) {
            return true; // The number is found
        }
    }
    return false; // The number is not found
}
template <typename T>
class NumX_O_Random_Player : public RandomPlayer<T>{
public:
    NumX_O_Random_Player (T symbol);
    void getmove(int &x, int &y,int &n) ;
    void getmove(int& x, int& y);
};
template <typename T>
void NumX_O_Player<T>::getmove (int& x, int& y) {
    const int GRID_SIZE = 3;    // Size of the board
    const int MIN_NUM = 1;     // Minimum allowed number
    const int MAX_NUM = 9;     // Maximum allowed number
    int number;
    while (true) {
        cout << this->name << ", enter your move (row, col, number): ";
        cin >> x >> y >> number;

        // Check if the input is valid
        if (cin.fail()) {
            cout << "Invalid input. Please enter numbers only.\n";
            cin.clear();
            continue;
        }

        // Check if move is within bounds
        if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
            cout << "Invalid position. Row and column must be between 0 and " << GRID_SIZE - 1 << ".\n";
            continue;
        }

        // Check if the number is in the valid range
        if (number < MIN_NUM || number > MAX_NUM) {
            cout << "Invalid number. Please choose a number between " << MIN_NUM << " and " << MAX_NUM << ".\n";
            continue;
        }

        // Check if the number matches the player's type (odd/even)
        if ((isOdd && number % 2 == 0) || (!isOdd && number % 2 != 0)) {
            cout << "Invalid number. "
                 << (isOdd ? "You must choose an odd number." : "You must choose an even number.")
                 << "\n";
            continue;
        }

        if (isNumberChosen(number)) {
            cout << "Invalid move. You have already chosen this number.\n";
            continue;
        }
        this->symbol=number;
        // Add the number to the player's chosen numbers
        chosenNumbers.push_back(number);
        break;
    }
}




//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include<bits/stdc++.h>
using namespace std;

// Constructor for NumX_O_Board
template <typename T>
NumX_O_Board<T>::NumX_O_Board() {
    this->rows = 3;
    this->columns = 3;
    this->board = new T*[this->rows]; // Allocate memory for rows

    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]; // Allocate memory for columns
    }

    // Initialize the board to 0 (or empty)
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}



template <typename T>
bool NumX_O_Board<T>::update_board(int x, int y, T num) {
    // Check if move is valid
    int number=int(num);
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        return false;
    }
    this->board[x][y] = number;
    this->n_moves++;
    return true;
}

// Display the board and the pieces on it
template <typename T>
void NumX_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << int(this->board[i][j]) << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
bool NumX_O_Board<T>::check_sum(int a, int b, int c) {
    return (a + b + c == 15);
}
// Returns true if there is any winner
template <typename T>
bool NumX_O_Board<T>::is_win() {
    // Check rows
    for (int i = 0; i < this->rows; i++) {
        if (check_sum(this->board[i][0], this->board[i][1], this->board[i][2])) return true;
    }

    // Check columns
    for (int i = 0; i < this->columns; i++) {
        if (check_sum(this->board[0][i], this->board[1][i], this->board[2][i])) return true;
    }

    // Check diagonals
    if (check_sum(this->board[0][0], this->board[1][1], this->board[2][2]) ||
        check_sum(this->board[0][2], this->board[1][1], this->board[2][0])) {
        return true;
        }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool NumX_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool NumX_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


//--------------------------------------

// Constructor for NumX_O_Player


// Constructor for NumX_O_Random_Player
template <typename T>
NumX_O_Random_Player<T>::NumX_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}


template <typename T>
void NumX_O_Random_Player<T>::getmove(int& x, int& y) {
    const int MIN_NUM = 1;     // Minimum allowed number
    const int MAX_NUM = 9;     // Maximum allowed number

    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    int number = MIN_NUM + (rand() % (MAX_NUM - MIN_NUM + 1)); // Random number between MIN_NUM and MAX_NUM
    this->symbol=number;
}

//-----------------------------
//non used virtuals

template <typename T>
void NumX_O_Random_Player<T>::getmove(int& x, int& y,int&n) {
}
template <typename T>
void NumX_O_Player<T>::getmove(int& x, int& y,int &n){}
#endif NumX_O_H