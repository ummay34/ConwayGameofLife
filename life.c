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

char **mutateGrid(int rows, int cols, char **grid) {
    char **newGrid = copyGrid(rows, cols, grid);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int currentState;
            int neighbors = nbrOfNeighbors(i,j,rows,cols,grid);
            if(grid[i][j] == '1'){
                currentState = 1;
            }
            else{
                currentState = 0;
            }
            if(currentState == 0 && neighbors == 3){
                newGrid[i][j] = '1';
            }
            else if (currentState == 1 && (neighbors < 2 || neighbors > 3)){
                newGrid[i][j] = '0';
            }
            else{
                newGrid[i][j] = grid[i][j];
            }
//            if (nbrOfNeighbors(i, j, rows, cols, grid) < 2 || nbrOfNeighbors(i, j, rows, cols, grid) > 3) {
//                newGrid[i][j] = '0';
//            }
//            if (nbrOfNeighbors(i, j, rows, cols, grid) == 2 || nbrOfNeighbors(i, j, rows, cols, grid) == 3) {
//                newGrid[i][j] = '1';
//            }
        }
    }
    return newGrid;
}

int wrap(int x,int N){
    return (x % N + N) %N;
}

// Returns the number of neighbors at postion (i,j) in the grid
int nbrOfNeighbors(int x, int y, int rows, int cols, char **grid) {
    int neighbors = 0;

//    for (int i = 0; i <=rows; i++) {
//        for (int j = 0; j <= cols; j++) {
//
//            //left side
//            if (grid[i][0]) {
//                //top left
//                if (grid[0][0]) {
//                    if (grid[0][j + 1] == '1') {
//                        neighbors++;
//                    }
//                    if (grid[i + 1][0] == '1') {
//                        neighbors++;
//                    }
//                    if (grid[i + 1][j + 1] == '1') {
//                        neighbors++;
//                    }
//                }
//                //bottom left case
//                if (grid[rows][0]) {
//                    if (grid[i - 1][0] == '1') {
//                        neighbors++;
//                    }
//                    if (grid[rows][j + 1] == '1') {
//                        neighbors++;
//                    }
//                    if (grid[i - 1][j + 1] == '1') {
//                        neighbors++;
//                    }
//                }
//
//                //middle
//                if(grid[rows > 0][0] && grid[rows][0]){
//
//                }
//
//            }
//            //top left
//            if (grid[0][0]) {
//                if (grid[0][j + 1] == '1') {
//                    neighbors++;
//                }
//                if (grid[i + 1][0] == '1') {
//                    neighbors++;
//                }
//                if (grid[i + 1][j + 1] == '1') {
//                    neighbors++;
//                }
//            }
//            //bottom left case
//            if (grid[rows][0]) {
//                if (grid[i - 1][0] == '1') {
//                    neighbors++;
//                }
//                if (grid[rows][j + 1] == '1') {
//                    neighbors++;
//                }
//                if (grid[i - 1][j + 1] == '1') {
//                    neighbors++;
//                }
//            }
//            //Bottom right
//            if (grid[rows][cols]) {
//                if (grid[i][j - 1] == '1') {
//                    neighbors++;
//                }
//                if (grid[i - 1][j] == '1') {
//                    neighbors++;
//                }
//                if (grid[i - 1][j - 1] == '1') {
//                    neighbors++;
//                }
//            }
//            if (grid[0][cols]) {
//                if (grid[i][j - 1] == '1') {
//                    neighbors++;
//                }
//                if (grid[i + 1][j] == '1') {
//                    neighbors++;
//                }
//                if (grid[i + 1][j - 1] == '1') {
//                    neighbors++;
//                }
//            }
//
//
//        }
//    }

    for(int i = -1; i < 2; i++){
        for(int j = 0; j < 2; j++){
			int col = wrap((x+i+cols),cols);
			int row = wrap((y + j + rows),cols);
            if(grid[row][col] == '1'){
                neighbors++;
            }
        }
    }


    //subtract 1 since we dont count the current cell 
    return neighbors;
}