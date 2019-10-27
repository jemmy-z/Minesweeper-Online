#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <server.h>

class MineSweeper{

private:
    int n;
    int m;
    int numMines;

    int** board;
    int** solutionBoard;

    bool grabable;

public:
    //n, m ,numMines
    MineSweeper();
    MineSweeper(int, int, int);

    void setGame(int, int, std::vector<std::tuple<int, int>>);
    void setMines(std::vector<std::tuple<int, int>>);
    void setGrabable(bool);
    minesweeper::json pushBoard();
    minesweeper::json pushCell(int, int);
    minesweeper::json clicked(int, int, int);   //r, c, state (1 = left, 2 = right, else = fail)
    
};

#endif