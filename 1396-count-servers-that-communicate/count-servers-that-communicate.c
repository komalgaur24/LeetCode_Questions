int countServers(int** grid, int gridSize, int* gridColSize) {

    int * rowCount = (int*)calloc(sizeof(int), gridColSize[0]);
    int * colCount = (int*)calloc(sizeof(int), gridSize);
    
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridColSize[0]; j++){

            if (grid[i][j] == 1){
                rowCount[j]++;
                colCount[i]++;
            }
        }
    }

    int total = 0;

    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridColSize[0]; j++){

            if (grid[i][j] == 1){
                if (rowCount[j] > 1 || colCount[i] > 1){
                    total++;
                }
            }
        }
    }

    return total;
}