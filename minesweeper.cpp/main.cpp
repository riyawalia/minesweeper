//
//  main.cpp
//
//  Created by Riya Walia on 2016-10-22.
//  Copyright © 2016 Riya Walia. All rights reserved.
//

#include <iostream>
using namespace std;

/*
 The mine is represented by a 8 by 8 grid, which is implemented by two dimensional arrays.
 Value Array: This array contains the "value" behind every tile in a mine. The "value" is a number
 between 0 and 8, where 0 denotes that the tile is a bomb and 1-8 denotes the
 number of bombs within the radius of the tile.
 
 Mine Array: This array is displayed to the user and represents the current state of the mine as
 to the user. Uncovered tiles are represented by '*'. Covered tiles are represented by
 its "value" (1 - 8). Marked tiles (marked as a bomb by the user) are represented by 'B'.
 
 Dynamics of the game: The mine has a maximum of 25 bombs which are randomly allocated to the tiles per
 execution of the program. Game is over once a bomb is uncovered. Game is won once
 all non-bomb tiles have been uncovered.
 */

int const size = 9; // mine displayed to the user is 8 by 8 but as first row and column are indexes, arrays are 9 by 9.

// helps in counting the number of bombs in radius of a tile
int bomb (int value) {
    if (value == 0) {
        return 1;
    }
    return 0;
}
// takes in a different array which is the "value array". Randomly allocates 0 and 1 to the tiles
// and makes sure that there are exactly 25 bombs.
void allocate_bombs(int values[size][size])
{   int const max_bombs = 25;
    int bombs = 0;
    while(bombs <= max_bombs) {
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
        std::cout<<"C: Enter a coordinate"<<std::endl;
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
