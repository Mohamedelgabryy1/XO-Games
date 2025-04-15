//
// Created by melta on 24/11/2024.
//

#ifndef XO_GAME_PYRAMIDX_O_H
#define XO_GAME_PYRAMIDX_O_H
#include "BoardGame_Classes.h"

template <typename T>
class PyramidX_O_Board:public Board<T> {
public:
    PyramidX_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class PyramidX_0_Player : public Player<T> {
public:
    PyramidX_0_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class PyramidX_0_Random_Player : public RandomPlayer<T>{
public:
    PyramidX_0_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for PyramidX_0_Board
template <typename T>
PyramidX_O_Board<T>::PyramidX_O_Board(){
    this->rows =3;
    this->columns=5;
    this->board = new char*[this->rows];
    for (int i = this->rows-1; i >= 0; i--) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
        this->columns-=2;
    }
    this->n_moves = 0;
}

template <typename T>
bool PyramidX_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if(!(x<0 || x>=this->rows)){
        switch(x) {
            case 0:
                if(y!=0)return false;
                else if(this->board[x][y] == 0|| mark == 0){
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
                break;
            case 1:
                if(y<0 ||y>2)return false;
                else if(this->board[x][y] == 0|| mark == 0){
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
                break;
            case 2:
                if(y<0 ||y>4)return false;
                else if(this->board[x][y] == 0|| mark == 0){
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
                break;
            default:
                break;

        }

    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void PyramidX_O_Board<T>::display_board() {
    this->columns=-1;
    for (int i = 0; i < this->rows; i++) {
        this->columns+=2;
        int padding=(5-this->columns)/2;
        for (int j = 0; j < padding; j++) {
            cout <<"          ";
        }
        cout << "| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n\n-------------------------------------------------\n\n";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool PyramidX_O_Board<T>::is_win() {
    // Check rows and columns
   if(((this->board[0][0]==this->board[1][0] && this->board[1][0]==this->board[2][0])
   ||(this->board[0][0]==this->board[1][3] && this->board[1][3]==this->board[2][5]))&&this->board[0][0]!=0) return true;

   if(this->board[0][0]==this->board[1][1] && this->board[1][1]==this->board[2][2] &&this->board[0][0]!=0) return true;
    if(this->board[1][0]==this->board[1][1] && this->board[1][1]==this->board[1][2] &&this->board[1][0]!=0) return true;
    for(int i=0;i<2;i++){
        if(this->board[2][i]==this->board[2][i+1] && this->board[2][i+1]==this->board[2][i+2] &&this->board[2][i]!=0) return true;
    }
    return false;
}
// Return true if 9 moves are done and no winner
template <typename T>
bool PyramidX_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool PyramidX_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for PyramidX_0_Player
template <typename T>
PyramidX_0_Player<T>::PyramidX_0_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void PyramidX_0_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for PyramidX_0_Random_Player
template <typename T>
PyramidX_0_Random_Player<T>::PyramidX_0_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void PyramidX_0_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
#endif //XO_GAME_PYRAMIDX_O_H
