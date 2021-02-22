## CIS343 - Conway's Game of Life Project
This project was created by Ummayair Ahmad and Kyle Jacobson for Structures of Programming Languages (CIS 343) during the Winter 2021 semester at Grand Valley State University.

This project was programmed using the C programming language on JetBrains' CLion IDE. GCC Handles all compilation and running for the project. 

It is a Game of Life simulation that is playable through the terminal using specific commands.

To run the game, first make sure
1) gcc is installed 

2)run the following command to compile program and generate a executable named "driver":  gcc -Wall -std=c99 -o driver driver.c life.c

3) Execute program using
  ./driver (filename) 
  
  **Files have to be in the following format" 
  " 3 3 0 1 0 0 1 0 0 0 1 " 
  
  First two ints are the # of rows and cols desired
  The rest of the ints will be the actual board we are loading, where 0 = dead cells and 1 = live cells. This must be proportionate to the size of the grid(Rows*cols)
  For example, in the example grid above we have a 3x3 board, so we should have 9 ints representing the whole board. 
  


-5 Functions in progress || 
- LoadFile : Complete 
- SaveFile : Complete
- CopyGrid : Complete
- MutateGrid : 80% done 
- CountNeighbors : Complete
