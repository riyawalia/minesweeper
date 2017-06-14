
### Summary
This is a console application written in C++, and is my representation of the classic game Minesweeper. 
The mine is represented by a 8 by 8 grid, which is implemented by a two-dimensional array. 

### User Interface 

The menu has three options
 
* New Game 
* Enter a coordinate
* Quit Game

### Value Array

This array (of integers) contains the "value" behind every tile in a mine. The "value" is a number
between 0 and 8, where 0 denotes that the tile is a bomb and 1-8 denotes the number of bombs within the radius of the tile.

### Mine Array 
This is an array (of characters) that is displayed on the console and represents the current state of the mine as uncovered by the user. Uncovered tiles are represented by '*'. Covered tiles are represented by its "value" ('1' - '8'). Marked tiles (marked as a bomb by the user) are represented by 'B'.

### Dynamics of the game 
The mine has a total of exactly 25 bombs which are randomly allocated to the tiles per
execution of the program. The game is over once a bomb is uncovered. The game is won once
all non-bomb tiles have been uncovered.
