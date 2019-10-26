#include <server.h>

class TicTacToe{

public:
    TicTacToe();

    void init();
    void setJoinable(bool);
    void reset();
    ucm::json pushGrid();
    ucm::json clicked(int, int);

private:
    int** grid;
    int currentPlayer = 1;

    bool joinable = false;
    int joinCode;
    int codeGen();
    int checkWinCondition();
    bool drawCondition();
    bool acceptClicks = true;
};
