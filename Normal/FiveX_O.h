//
// Created by Lenovo on 11/26/2024.
//

#ifndef FIVEX_O_H
#define FIVEX_O_H


#include "BoardGame_Classes.h"

template <typename T>
class FiveX_O_Board : public Board<T> {
public:
    FiveX_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void count_patterns();
    void reset_counters();

private:

    int Xcounter=0;
    int Ocounter=0;
    char mark;

};

template <typename T>
class FiveX_O_Player : public Player<T> {
public:
    FiveX_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

    int n_moves;
};

template <typename T>
class FiveX_O_Random_Player : public RandomPlayer<T>{
public:
    FiveX_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
    int n_moves;
};






//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;


template <typename T>
FiveX_O_Board<T>::FiveX_O_Board() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize all cells to 0 (empty)
        }
    }
    this->n_moves = 0;
    reset_counters();  // Initialize counters to 0 at the start of the game
}

template <typename T>
bool FiveX_O_Board<T>::update_board(int x, int y, T mark) {
    this->mark=mark;
    if (this->n_moves==24) {
        this->n_moves++;
        return true;
    }

    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;  // Clear the cell
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);  // Place the mark (X or O)
        }
        return true;
    }
    return false;
}

template <typename T>
void FiveX_O_Board<T>::display_board() {
    system("CLS");
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------------------------";
    }
    cout << endl;
}

template <typename T>
void FiveX_O_Board<T>::reset_counters() {
    Xcounter = 0;
    Ocounter = 0;
}

template<typename T>
void FiveX_O_Board<T>::count_patterns() {
    reset_counters();

    // Check rows
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= 2; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2]) {
                if (this->board[i][j] == 'X') Xcounter++;
                else if (this->board[i][j] == 'O') Ocounter++;
            }
        }
    }

    // Check columns
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i <= 2; i++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i + 1][j] == this->board[i + 2][j]) {
                if (this->board[i][j] == 'X') Xcounter++;
                else if (this->board[i][j] == 'O') Ocounter++;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2]) {
                if (this->board[i][j] == 'X') Xcounter++;
                else if (this->board[i][j] == 'O') Ocounter++;
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= 2; i++) {
        for (int j = 2; j < 5; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i + 1][j - 1] == this->board[i + 2][j - 2]) {
                if (this->board[i][j] == 'X') Xcounter++;
                else if (this->board[i][j] == 'O') Ocounter++;
            }
        }
    }
}


template <typename T>
bool FiveX_O_Board<T>::is_win() {
    if (this->n_moves>=24) {
        count_patterns();
        if (Xcounter > Ocounter && mark=='X') {
            cout<<"Score: "<<"X :"<<Xcounter<<",O :"<<Ocounter<<endl;
            return true;
        }
        else if (Xcounter < Ocounter && mark == 'O') {
            cout<<"Score: "<<"X :"<<Xcounter<<",O :"<<Ocounter<<endl;
            return true;
        }
        else return false;
}
    return false;
}

// Return true if 24 moves are done and no winner
template <typename T>
bool FiveX_O_Board<T>::is_draw() {
    return (this->n_moves == 25 && !is_win());
}

template <typename T>
bool FiveX_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for PyramidX_0_Player
template <typename T>
FiveX_O_Player<T>::FiveX_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FiveX_O_Player<T>::getmove(int& x, int& y) {
    if (this->n_moves==12){return;}
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
    this->n_moves++;
}

// Constructor for X_O_Random_Player
template <typename T>
FiveX_O_Random_Player<T>::FiveX_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    if (this->n_moves==12){return;}
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    this->n_moves++;
}

template <typename T>
void FiveX_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}



#endif //FIVEX_O_H