#include<bits/stdc++.h>
using namespace std;

class Game {
private:
    int BoardSize;
    int NumberOfSnakes;
    int NumberOfLadders;
    int board[1000000];      //implementing the board as 1D array
    int Destination;
public:
    Game(int boardsize) {
        BoardSize = boardsize;
        int x = BoardSize * BoardSize;
        Destination = x;

        NumberOfLadders = x / 8 + rand() % (x / 8);    //Randomly chosing number of ladders and snakes

        NumberOfSnakes = x / 8 + rand() % (x / 8);    //max ladders and snakes can be (total cells)/4 each
    }                                                 //to make the game interesting

    void setBoard() {
        int x = BoardSize * BoardSize;
        for (int i = 1; i <= x; i++)
            board[i] = 0;
        vector<int>v;
        for (int i = 1; i < x; i++)
            v.push_back(i);
        int p = NumberOfLadders;
        while (p--) {
            int s = rand() % v.size();
            int start = v[s];
            v.erase(v.begin() + s);
            int t = rand() % v.size();
            int end = v[t];
            v.erase(v.begin() + t);
            board[start] = end;
        }
        p = NumberOfSnakes;
        while (p--) {
            int s = rand() % v.size();
            int start = v[s];
            v.erase(v.begin() + s);
            int t = rand() % v.size();
            int end = v[t];
            v.erase(v.begin() + t);
            board[end] = start;
        }
    }

    int valueAt(int pos) {
        return board[pos];
    }

    int destinationcell() {
        return Destination;
    }
    void show() {
        for (int i = 1; i <= Destination; i++) cout << board[i] << ' ';
        cout << endl;
    }
    int dice() {
        return 1 + rand() % 6;
    }

};

class player {
private:
    string Name;
    int Position;
public:
    player(string name) {
        Name = name;
        Position = 1;
    }
    int currentPosition() {
        return Position;
    }
    string NameofPlayer() {
        return Name;
    }
    void move(int dicevalue, Game &tmp) {
        if (dicevalue + Position > tmp.destinationcell()) return;
        Position += dicevalue;
        int valueAtPosition = tmp.valueAt(Position);
        if (valueAtPosition)
            Position = valueAtPosition;
    }
};

int main() {
    srand(time(0));
    int boardsize;
    cout << "What size of board do you prefer?\n";
    cin >> boardsize;
    int destination = boardsize * boardsize;
    int MaxMoves = 2 * destination; //game ends after a large number of moves

    Game SnakeAndLadder(boardsize);
    SnakeAndLadder.setBoard();
    SnakeAndLadder.show();
    string name;
    cout << "Enter name of the first player\n";
    cin >> name;
    player p1(name);
    cout << "Enter name of the second player\n";
    cin >> name;
    player p2(name);
    int rolldie;
    while (MaxMoves--) {
        cout << p1.NameofPlayer() << "'s turn, enter any number to roll the die\n";
        cin >> rolldie;
        int p1roll = SnakeAndLadder.dice();
        p1.move(p1roll, SnakeAndLadder);
        cout << p2.NameofPlayer() << "'s turn, enter any number to roll the die\n";
        cin >> rolldie;
        int p2roll = SnakeAndLadder.dice();
        p2.move(p2roll, SnakeAndLadder);
        if (p1.currentPosition() == destination || p2.currentPosition() == destination)
            break;
    }
    if (p1.currentPosition() > p2.currentPosition())
        cout << p1.NameofPlayer() << " won!" << endl;
    else if (p1.currentPosition() < p2.currentPosition())
        cout << p2.NameofPlayer() << " won!" << endl;
    else
        cout << "Match tied!" << endl;
    return 0;
}
