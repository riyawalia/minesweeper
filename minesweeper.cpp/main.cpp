//
//  main.cpp
//
//  Created by Riya Walia on 2016-10-22.
//  Copyright © 2016 Riya Walia. All rights reserved.
//

#include <iostream>
using namespace std;


int const size = 9; // mine displayed to the user is 8 by 8 but as first row and column are indexes, arrays are 9 by 9.
int const total_bombs = 25;

// helps in counting the number of bombs in radius of a tile
int bomb (int value) {
    if (value == 0) {
        return 1;
    }
    return 0;
}
// takes in a different array which is the "value array". Randomly allocates 0 and 1 to the tiles
// and makes sure that there are exactly "total_bombs" number of bombs
void allocate_bombs(int values[size][size])
{   int bombs = 0;
    while(bombs <= total_bombs) {
        for (int i = 1; i < size ; ++i)
            for (int j = 1; j < size; ++j) {
                values[i][j] = rand() % 2;
                if (values[i][j] == 0) {
                    ++bombs;
                }
            }
    }
}
// displays the mine
void display_mine(char mine[size][size])
{
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j <size; ++j) {
            std::cout<< mine[i][j]<<"            ";
        }
        std::cout<<std::endl<<endl<<endl;
    }
}

bool check_game_won(char mine[size][size], int values[size][size]) {
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            // if tile is not a bomb but is uncovered, game has not been won.
            if (values[i][j] > 0 && mine[i][j] == '*') {
                return false;
            }
        }
    }
    return true;
}

// checks if coordinate entered is a bomb tile
// if yes, then it displays the mine again with the bomb tile showing
// otherwise, it just displays the mine again with teh clear tile showing
void check_for_bomb(char mine[size][size],int values[size][size])
{   int r,c, bomb;
    std::cout<<"Enter row number: "<<std::endl;
    std::cin>>r;
    std::cout<<"Enter column number: "<<std::endl;
    std::cin>>c;
    std::cout<<"To mark this as a bomb, enter 0. Otherwise enter 1."<<std::endl;
    std::cin>>bomb;
    if (bomb == 1) {
        if(values[r][c] != 0) {
            mine[r][c] = 48 + values[r][c]; // uncovers tile
            if (check_game_won(mine, values)) {
                std::cout<<"Congratulations! You won the game! "<<endl;
                return;
            }
            display_mine(mine);
        }
        else std::cout<<"Sorry! Game over."<<endl;
    }
    else if (bomb == 0) {
        mine[r][c] = 'B'; display_mine(mine);
    }
    else std::cout<<"Invalid input. Try again!"<<endl;
}
// takes in the value array and allocates count of neighbouring bombs to non-bomb tiles
void allocate_count (int values[size][size]) {
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            if (values[i][j] == 0 && i != 0 && j !=0 ) { // if tile is not a bomb nor an index i.e. uncovered
                values[i][j] = bomb(values[i - 1][j]) + bomb(values[i + 1][j]) +
                               bomb(values[i][j + 1]) + bomb(values[i][j - 1]) +
                               bomb(values[i - 1][j - 1]) + bomb(values[i + 1][j + 1]);
            }
        }
    }
}
// Creates a new mine for a new game
void new_mine(char mine[size][size]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // allocating indexes for first row and column
            if (i == 0) {
                mine[i][j] = j + '0';
            }
            else if (j == 0) {
                mine[i][j] = i + '0';
            }
            // alocating uncovered tiles:
            else {
                mine[i][j] = '*';
            }
        }
    }
}

int main() {
    char command;
    int values[size][size];
    char mine[size][size];
    // menu:
    while(1) // switch case breaks out of the loop
    {
        std::cout<<"Please choose an option"<<std::endl;
        std::cout<<"N: New Game"<<std::endl;
        std::cout<<"C: Enter a coordinateNQ"<<std::endl;
        std::cout<<"Q: Quit Game"<<std::endl;
        std::cin>>command;
        switch(toupper(command)) {
            case 'N':   new_mine(mine);
                        display_mine(mine);
                        allocate_bombs(values);
                        allocate_count(values);
                break;
            case 'C':   check_for_bomb(mine,values);
                break;
            case 'Q': return 0;
                break;
            default: std::cout<<"Invalid input. Try again!"<<endl;
                break;
        }
    }
    return 0;
}
