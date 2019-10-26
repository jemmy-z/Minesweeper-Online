#include <server.h>

class MineSweeper{

private:
    int n = 3;
    int m = 3;
    int numMines = 1;

    int** board;
    int** solutionBoard;

public:
    MineSweeper(tuple<int, int>[]);

    minesweeper::json pushBoard();
    minesweeper::json pushCell(int, int);
    minesweeper::json clicked(int, int, int)   //r, c, state (1 = left, 2 = right, else = fail)
    
};