//
// Created by melta on 25/11/2024.
//

#ifndef XO_GAME_WORDX_O_H
#define XO_GAME_WORDX_O_H
#include "BoardGame_Classes.h"

template <typename T>
class WordX_O_Board:public Board<T> {
public:
    WordX_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
private:
    unordered_map<string,int> dictionary;
};

template <typename T>
class WordX_O_Player : public Player<T> {
public:
    WordX_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class WordX_O_Random_Player : public RandomPlayer<T>{
public:
    WordX_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>// for toupper()

using namespace std;

// Constructor for WordX_O_Board
template <typename T>
WordX_O_Board<T>::WordX_O_Board() {
    ifstream file;
    string path;
    cout<<"Enter file for word reference: "<<endl;
    cin>>path;
    file.open(path);
    while(!file.is_open()){
         cin.clear();
         cin.ignore(INT_MAX,'\n');
         cout<<"Invalid file \n Enter file for word reference: \n";
         cin>>path;
        file.open(path);
    }
    string word;
    int iteration=1;
    while(file>>word){
        dictionary[word]=iteration++;
    }
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool WordX_O_Board<T>::update_board(int x, int y, T mark) {
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
void WordX_O_Board<T>::display_board() {
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

// Returns true if there is any winner
template <typename T>
bool WordX_O_Board<T>::is_win() {
    // Check rows and columns
    string word="";
    for (int i = 0; i < this->rows; i++) {

        word+=this->board[i][0];
        word+=this->board[i][1];
        word+=this->board[i][2];
        if(dictionary.find(word)!=dictionary.end()) return true;
        word="";
        word+=this->board[0][i];
        word+= this->board[1][i];
        word+= this->board[2][i];
        if(dictionary.find(word)!=dictionary.end()) return true;
        word="";
    }
    // Check diagonals
    word+=this->board[0][0];
    word+= this->board[1][1];
    word+=this->board[2][2];
    if(dictionary.find(word)!=dictionary.end()) return true;
    word="";
    word+=this->board[2][0];
    word+=this->board[1][1];
    word+=this->board[0][2];
    if(dictionary.find(word)!=dictionary.end()) return true;
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool WordX_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool WordX_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for WordX_O_Player
template <typename T>
WordX_O_Player<T>::WordX_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void WordX_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout<<"\n enter letter: ";
    cin>>this->symbol;
}

// Constructor for WordX_O_Random_Player
template <typename T>
WordX_O_Random_Player<T>::WordX_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void WordX_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    this->symbol=char((rand() % 26)+65);
}
#endif //XO_GAME_WORDX_O_H
