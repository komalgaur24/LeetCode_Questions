bool backtrack(char** board, int boardSize, int boardColSize, int r, int c,
               char* word, int wordIdx) {
    // Base case: all chars found in grid
    if (wordIdx == strlen(word))
        return true;

    // Handle the boundaries
    if (r < 0 || c < 0 || r >= boardSize || c >= boardColSize ||
        board[r][c] != word[wordIdx])
        return false;

    // avoid repitition of paths during backtrack by replacing matched char to $
    board[r][c] = '$';

    // used to explore adjacent cells
    int x[4] = {0, 1, 0, -1};
    int y[4] = {1, 0, -1, 0};
    for (int j = 0; j < 4; j++)
        if (backtrack(board, boardSize, boardColSize, r + x[j], c + y[j], word,
                      wordIdx + 1))
            return true;
    
    // restore the char for next search path
    board[r][c] = word[wordIdx];
    return false;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    for (int r = 0; r < boardSize; r++)
        for (int c = 0; c < *boardColSize; c++)
            if (backtrack(board, boardSize, *boardColSize, r, c, word, 0))
                return true;
    return false;
}