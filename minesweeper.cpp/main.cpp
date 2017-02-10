//
//  main.cpp
//  helloworld.cpp
//
//  Created by Riya Walia on 2016-10-22.
//  Copyright © 2016 Riya Walia. All rights reserved.
//

#include <iostream>
using namespace std;
int bomb (int c) {
    if (c==0) return 1;
    else return 0;
}
// takes in a different array which is the "value array". Randomly allocates 0 and 1 to the tiles
// and makes sure that there are exactly 25 bombs.
void allocate_bombs(int V[9][9])
{ int max=0;
    while(max<=25) {
    for (int i=1; i<9 ; i++)
        for (int j=1; j<9; j++)
        { V[i][j]= rand()%2;
            if (V[i][j]==0) max++; }
}
}
// displays the mine
void display_mine(char M[9][9])
{
    for(int i=0; i<=8; i++)
    {
        for(int j=0; j<=8; j++)
            std::cout<< M[i][j]<<"            ";
        std::cout<<std::endl<<endl<<endl; }
}


// checks if coordinate entered is a bomb tile
// if yes, then it displays the mine again with the bomb tile showing
// otherwise, it just displays the mine again with teh clear tile showing
void checkforbomb(char M[9][9],int V[9][9])
{   int r,c, bomb;
    std::cout<<"Enter row number: "<<std::endl;
    std::cin>>r;
    std::cout<<"Enter column number: "<<std::endl;
    std::cin>>c;
    std::cout<<"To mark this as a bomb, enter 0. Otherwise enter 1."<<std::endl;
    std::cin>>bomb;
    if (bomb==1) {
        if(V[r][c]!=0) {
            M[r][c]= 48+V[r][c]; //displays count of tile
            display_mine(M); }
        else std::cout<<"Sorry! Game over. You suck."<<endl;;
        
    }
    if (bomb==0) {
    M[r][c]='B'; display_mine(M);
  }
    else std::cout<<"Invalid input. Try again!"<<endl;
}
// takes in the value array and allocates count of neighbouring bombs to non-bomb tiles
void allocate_count (int V[9][9]) {
    for (int i=1; i<=8; i++)
        for (int j=1;j<=8;j++)
            if(V[i][j]==0 && i!=0 && j!=0)
                V[i][j]= bomb(V[i-1][j])+bomb(V[i+1][j])+bomb(V[i][j+1])+
                         bomb(V[i][j-1])+bomb(V[i-1][j-1])+bomb(V[i+1][j+1]);
}

int main() {
    int answer;
// making my value array:
    int V[9][9];
// making my display array:
    char M[9][9];
    for (int i=1; i<9; i++)
        for (int j=1; j<9; j++)
            M[i] [j]= '*';
    for (int a=0; a<9; a++) M[0][a]=a+48;
    for (int b=0; b<9; b++) M[b][0]=b+48;
// menu:
    do
    {
        std::cout<<"Please choose an option"<<std::endl;
        std::cout<<"1. New Game"<<std::endl;
        std::cout<<"2. Enter a coordinate"<<std::endl;
        std::cout<<"3. End Game"<<std::endl;
        std::cin>>answer;
        switch(answer) {
            case 1:   display_mine(M); allocate_bombs(V); allocate_count(V);
                break;
            case 2:   checkforbomb(M,V);
                break;
                default: std::cout<<"Invalid input. Try again!"<<endl;
                break;
        }
    }
    while (answer!=3);
    return 0;
}


