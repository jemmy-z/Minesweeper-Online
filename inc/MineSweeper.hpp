#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <server.h>

class MineSweeper{

private:
    int n;
    int m;
    int numMines;
    int minesLeft;

    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> solutionBoard;

    bool grabable;
    bool firstClick;

public:
    //n, m ,numMines
    MineSweeper();
    void setDefaults(int, int, int);

    void setGame(int, int, std::vector<std::tuple<int, int>>);
    void setMines(std::vector<std::tuple<int, int>>);
    void setGrabable(bool);
    minesweeper::json pushBoard();
    int pushCell(int, int);
    int clicked(int, int, int);   //r, c, state (1 = left, 2 = right, else = fail)
    void groupClear(int, int);     //when clicked cell is 0, clear all zeros
    bool getGrabable();
    int getMinesLeft();
    bool verifyWin();
};

#endif