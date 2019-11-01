#include <MineSweeper.hpp>

/*
    Board int States
    0-8 = # adjacent mines
    10 = bomb
    -1 = hidden
*/
MineSweeper::MineSweeper(){
}

void MineSweeper::setDefaults(int n, int m, int numMines){
    this->n = n;
    this->m = m;
    this->numMines = numMines;
    this->minesLeft = numMines;
    this->grabable = false;

    //Init board to be hidden
    for (int i = 0 ; i < n ; i++){
        board.push_back({});
        solutionBoard.push_back({});
        for(int j = 0 ; j < m ; j++){
            board[i].push_back(-1);               //Init board to all -1
            solutionBoard[i].push_back(0);        //Init solu board to all 0
        }
    }
}

void MineSweeper::setGame(int r, int c, std::vector<std::tuple<int, int>> mineLoc){
    setDefaults(r,c,mineLoc.size());
    setMines(mineLoc);
}

void MineSweeper::setMines(std::vector<std::tuple<int, int>> mineLoc){
    //set mines in solution board
    int n = board.size();
    int m = board[0].size();

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
			    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                if(solutionBoard[ny][nx] != 10){        //Dont increment bomb cells
                    solutionBoard[ny][nx] += 1;
                }
		    }
	    }
    }
}


void MineSweeper::setGrabable(bool b){
    this->grabable = b;
}

minesweeper::json MineSweeper::pushBoard(){
    minesweeper::json result;
    for(int r = 0 ; r < n ; r++){
		std::vector<int> fin = {};
		for (int c = 0 ; c < m ; c++){
			fin.push_back(board[r][c]);
 		}
		result.push_back(fin);
	}
    return result;
}

int MineSweeper::pushCell(int r, int c){
    return solutionBoard[r][c];
}

int MineSweeper::clicked(int r, int c, int clickType){

    if(clickType = 1){
        if(board[r][c] != -1) return 0;
        if(solutionBoard[r][c] == 10){      //If clicked cell is a bomb
            grabable = false;               //Effectively ending game   
        }                              //Update cell State
        board[r][c] = solutionBoard[r][c];
        return 1;           //Return sucess
    }else if(clickType == 2){               //If Right Click
        if(board[r][c] == -1){              //Check if clicked cell is hidden
            board[r][c] = 10;               // mark r,c as a bomb
            --numMines;
            return 1;           //Return sucess
        }else{
            return 0;           //If right clicking visable cell, error
        }
    }else{                                  //If click type is anything else, error
        return 0;
    }
}

void MineSweeper::groupClear(int r, int c){
    //Look at all adjacent cells;
    for(int i = -1 ; i <= 1 ; i++){
		for(int j = -1 ; j <= 1; j++){
            //Check if is same cell
			if(i == 0 && j == 0) continue;
			int nx = c + j;
			int ny = r + i;
            //Check if new cell out of bounds
			if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            //Check if cell hidden
            if(board[ny][nx] != -1) continue;

            int cellValue = solutionBoard[ny][nx];

            if(cellValue == 0){        
                board[ny][nx] = cellValue;
                groupClear(ny, nx);
            }else{
                board[ny][nx] = cellValue;
            }
		}
	}
}

bool MineSweeper::getGrabable(){
    return grabable;
}

int MineSweeper::getMinesLeft(){
    return minesLeft;
}