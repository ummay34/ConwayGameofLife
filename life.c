//***************************************************
// Filename: life.c
//
// Author(s): Ummayair Ahmad, Kyle Jacobson
//***************************************************

#include "life.h"

// Constructs and returns a string (printable) representation of the grid.
char *toString(int rows, int cols, char **grid) {
    char *str = (char *) calloc(4 * rows * cols, sizeof(char));
    char *ptr = str;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '0') {
                sprintf(ptr, " . ");
            } else {
                sprintf(ptr, " X ");
            }
            ptr += 3;;
        }
        sprintf(ptr, "\n");
        ptr++;
    }
    return str;
}

// Creates a grid of rows x cols and initializes the grid with data from specified file
char **loadGridFromFile(char *filename, int *rows, int *cols) {
    // Char **grid = NULL;
    char buf[1024]; // max length of line in input file
    FILE *file = fopen(filename, "r");

    // Read line from file.
    fgets(buf, 1024, file);
    fclose(file);

    // Get number of rows from the line read.
    *rows = atoi(strtok(buf, " "));

    // Get number of columns from the line read.
    *cols = atoi(strtok(NULL, " "));

    // Create the base gameGrid and allocate memory.
    char **gameGrid = (char **) malloc(*rows * sizeof(char *));
    for (int i = 0; i < *rows; i++) {
        gameGrid[i] = (char *) malloc(*cols * sizeof(char));
    }

    // Iterate and assign values from .gol files to the gameGrid.
    for (int temp = 0; temp < *rows; temp++) {
        // Iterates through the columns on the gameGrid.
        for (int j = 0; j < *cols; j++) {
            // Takes value from the .gol file and places it on the gameGrid.
            gameGrid[temp][j] = strtok(NULL, " ")[0];
        }
    }
    // Return the gameGrid to the user.
    return gameGrid;
}

// Saves the grid data to the specified file
void saveGridToFile(char *filename, int rows, int cols, char **grid) {
    //"W" flag = writing files
    //"R" Flag = reading, a = append
    FILE *file = fopen(filename, "w");

    // Prints the rows and columns of the grid.
    fprintf(file, "%d ", rows);
    fprintf(file, "%d ", cols);

    // Iterates through the rows of the grid.
    for (int i = 0; i < rows; i++) {
        // Iterates through the columns of the grid.
        for (int j = 0; j < cols; j++) {
            // Prints the char at the current position on the grid.
            fprintf(file, "%c ", grid[i][j]);
        }
    }
    // Close the file that is being used.
    fclose(file);
}

// Creates and returns a new grid that is a duplicate of the game grid.
char **copyGrid(int rows, int cols, char **grid) {
    // Create a duplicate grid and allocate memory.
    char **dup = (char **) malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        dup[i] = (char *) malloc(cols * sizeof(char *));
    }

    // Iterates through the rows of the grid.
    for (int i = 0; i < rows; i++) {
        // Iterates through the columns of the grid.
        for (int j = 0; j < cols; j++) {
            // Take the current value on gameGrid and transfer it to duplicate grid.
            dup[i][j] = grid[i][j];
        }
    }

    // Return the duplicate grid to the user.
    return dup;
}

char **mutateGrid(int rows, int cols, char **grid) {
    // Take the duplicate grid and assign it to a newly created grid.
    char **newGrid = copyGrid(rows, cols, grid);

    // Iterates through  the rows of the grid.
    for (int i = 0; i < rows; i++) {
        // Iterates through the columns of the grid.
        for (int j = 0; j < cols; j++) {
            // Obtain the number of neighbors that exist around a current cell.
            int neighbors = nbrOfNeighbors(i, j, rows, cols, grid);

            // If the cell is currently live.
            if (grid[i][j] == '1') {
                // A live cell with less than two live neighbors or more than three neighbors dies.
                if (neighbors < 2 || neighbors > 3) {
                    newGrid[i][j] = '0';
                }

                // A live cell with two or three live neighbors lives.
                if (neighbors == 2 || neighbors == 3) {
                    newGrid[i][j] = '1';
                }
            }

            // If the cell is currently dead.
            else{
                // A dead cell with three live neighbors becomes live.
                if (neighbors == 3) {
                    newGrid[i][j] = '1';
                }
            }
        }
    }
    // Return the newly created grid for the user.
    return newGrid;
}

// Counts the number of neighbors around a specific cell.
int nbrOfNeighbors(int x, int y, int rows, int cols, char **grid) {
    // Variable for tracking the count of neighbors.
    int neighbors = 0;

    // Iterate through the rows.
    for (int i = -1; i < 2; i++) {
        // Iterate through the columns.
        for (int j = -1; j < 2; j++) {
            // Checks if current iteration is current position (x,y).
            if (!(i == 0 && j == 0)) {
                // Checks if surrounding cells are live.
                if (grid[(x + i + rows) % rows][(y + j + cols) % cols] == '1') {
                    // If so, add to the neighbors count.
                    neighbors++;
                }
            }
        }
    }
    // Return neighbors to the user.
    return neighbors;
}
