/* rule description from https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life:
These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

Any live cell with two or three live neighbours survives.
Any dead cell with three live neighbours becomes a live cell.
All other live cells die in the next generation. Similarly, all other dead cells stay dead.    
*/

// approach 1 : construct neighbor matrix
// approach 2 : state machine, i.e. live->dead, set the value = -1 & dead->live, set the value = 2 temporarily


void gameOfLife(vector<vector<int>>& board) {
    int rows = board.size();
    if (rows == 0) return;
    int cols = board[0].size();


    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int liveNeighbors = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if ( (dr != 0 || dc != 0)) {
                        int r = row + dr;
                        int c = col + dc;
                        if (r >= 0 && r < rows && c >= 0 && c < cols && abs(board[r][c]) == 1) {
                            liveNeighbors += 1;    
                        }
                    }
                }
            }
            // rule 1,3
            if (board[row][col] == 1 && (liveNeighbors < 2 || liveNeighbors > 3)) {
                board[row][col] = -1;
            }
            // rule 4
            if (board[row][col] == 0 && liveNeighbors == 3) {
                board[row][col] = 2;
            }
        }
    }

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            if (board[row][col] > 0) {
                //rules
                board[row][col] = 1;
            } else{
                board[row][col] = 0;
            }
        }
    }
}
