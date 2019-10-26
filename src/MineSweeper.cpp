#include <MineSweeper.hpp>

/*
    Board int States
    0-9 = # adjacent mines
    10 = bomb
    -1 = hidden
*/
MineSweeper::MineSweeper(){
}

MineSweeper::MineSweeper(int n, int m, int numMines){
    this->n = n;
    this->m = m;
    this->numMines = numMines;

    //Init board to be hidden
    board = new int*[n];
    solutionBoard = new int*[n];
    for (int i = 0 ; i < n ; i++){
        board[i] = new int[m];
        solutionBoard[i] = new int[m];
        for(int j = 0 ; j < m ; j++){
            board[i][j] = -1;               //Init board to all -1
            solutionBoard[i][j] = 0;        //Init solu board to all 0
        }
    }
}

void MineSweeper::setMines(std::vector<std::tuple<int, int>> mineLoc){
    //set mines in solution board
    for(int i = 0 ; i < mineLoc.size() ; i++){
        int r = std::get<0>(mineLoc[i]);
        int c = std::get<1>(mineLoc[i]);

        solutionBoard[r][c] = 10;       //set bomb

        //Increase neighboor bomb count
        for(int i = -1 ; i <= 1 ; i++){
		    for(int j = -1 ; j <= 1; j++){
			    if(i == 0 && j == 0) continue;
			        int nx = c + j;
			        int ny = r + i;
			    if (nx < 0 || nx == m || ny < 0 || ny == n) continue;
                if(solutionBoard[ny][nx] != 10){        //Dont increment bomb cells
                    solutionBoard[ny][nx] += 1;
                }
		    }
	    }
    }
}

//Depreceated
minesweeper::json MineSweeper::pushBoard(){
    minesweeper::json result;
    for(int r = 0 ; r < 3 ; r++){
		std::vector<int> fin = {};
		for (int c = 0 ; c < 3 ; c++){
			fin.push_back(board[r][c]);
 		}
		result.push_back(fin);
	}
    return result;
}

minesweeper::json MineSweeper::pushCell(int r, int c){
    minesweeper::json result;
    result["value"] = solutionBoard[r][c];
    return result;
}

minesweeper::json MineSweeper::clicked(int r, int c, int clickType){
    minesweeper::json result;

    if(clickType = 1){
        if(solutionBoard[r][c] == 10){
            result["result"] = 0;
            return result;
        }else{
            board[r][c] = solutionBoard[r][c];
        }
    }else if(clickType == 2){
        board[r][c] = 10;               // mark r,c as a bomb
    }else{
        result["result"] = 0;
        return result;
    }
    result["result"] = 1;
    return result;
}
