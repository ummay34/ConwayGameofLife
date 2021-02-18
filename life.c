//***************************************************
// Filename: life.c
//
// Author(s): 
//***************************************************

#include "life.h"

// Constructs and returns a string (printable) representation of the grid
char *toString(int rows, int cols, char **grid)
{
	char *str = (char *) calloc(4 * rows * cols, sizeof(char));
	char *ptr = str;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '0') {
                sprintf(ptr," . ");
            } else {
                sprintf(ptr," X ");
            }
			ptr += 3;;
		}
		sprintf(ptr,"\n");
		ptr++;
	}

	return str;
}

// Creates a grid of rows x cols and initializes the grid with data from specified file
char **loadGridFromFile(char *filename, int *rows, int *cols)
{
   // char **grid = NULL;
    char buf[1024]; // max length of line in input file
    FILE *file = fopen(filename,"r");

    // read line from file
    fgets(buf,1024,file);
    fclose(file);

    // get number of rows from the line read
    *rows = atoi(strtok(buf," "));

    // get number of columns from the line read
    *cols = atoi(strtok(NULL," "));

    //idk if i have to this
    int rowCnt = *rows;
    int ColCnt = *cols;

    //allocate memory for gamegrid
    char **gameGrid = (char **)malloc(rowCnt * sizeof(char * ));
    for (int i = 0; i < rowCnt; i++){
        gameGrid[i] = (char *)malloc(ColCnt * sizeof(char));
    }

    //assign values from file;
    for(int temp = 0; temp < rowCnt; temp++){
        for(int j = 0; j < ColCnt; j++){
            //strtok method takes input using a " " seperator
            //[0] is needed at the end because strtok returns an array of chars(string)
            //even though our array is only size 1 because we have 1 element between each " " seperator. we still have to use that notation to get the value.
            gameGrid[temp][j] = strtok(NULL," ")[0];
        }
    }


    return gameGrid;
}

// Saves the grid data to the specified file
void saveGridToFile(char *filename, int rows, int cols, char **grid)
{
    //"W" flag = writing files
    //"R" Flag = reading, a = append
    FILE *file = fopen(filename,"w");

    fprintf(file, "%d ",rows);
    fprintf(file, "%d ",cols);

    for(int i =0; i < rows; i++){
        for(int j=0; j < cols; j++){
            fprintf(file, "%c ",grid[i][j]);
        }
    }

    // COMPLETE THIS PART OF THIS FUNCTION
    fclose(file);
}

// Creates and returns a new grid that is a duplicate of the given grid
char **copyGrid(int rows, int cols, char **grid)
{
    char **dup = (char **)malloc(rows * sizeof(char * ));
    for (int i = 0; i < rows; i++){
        dup[i] = (char *)malloc(cols * sizeof(char));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dup[i][j] = grid[i][j];

        }
    }
    return dup;
}

// Mutates the given grid one generation and return a new grid
char **mutateGrid(int rows, int cols, char **grid)
{
	char** newgrid = copyGrid(rows,cols,grid);

	// COMPLETE THIS PART OF THIS FUNCTION

	return newgrid;
}

// Returns the number of neighbors at postion (i,j) in the grid
int nbrOfNeighbors(int i, int j, int rows, int cols, char **grid)
{
	int neighbors = 0;

	// COMPLETE THIS PART OF THIS FUNCTION

	return neighbors;
}
