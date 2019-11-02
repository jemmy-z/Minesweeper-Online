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
    this->firstClick = true;

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

/*Function args: vector of tuple containing valid r,c pairs
  returns: void

    Iterate through vector of tuples, places mine on solution board, and increase surround cell nums
*/
void MineSweeper::setMines(std::vector<std::tuple<int, int>> mineLoc){
    //set mines in solution board
    int n = board.size();
    int m = board[0].size();

    for(int index = 0 ; index < mineLoc.size() ; index++){
        int r = std::get<0>(mineLoc[index]);
        int c = std::get<1>(mineLoc[index]);

        solutionBoard[r][c] = 10;       //set bomb

        //Increase neighboor bomb count
        for(int i = -1 ; i <= 1 ; i++){
		    for(int j = -1 ; j <= 1; j++){
			    if(i == 0 && j == 0) continue;                                      //skip center
			    int nx = c + j;
			    int ny = r + i;
			    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;               //Bounds check
                if(solutionBoard[ny][nx] != 10){                                    //Dont increment bomb cells
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

/*Function args: row, col, and click type
  Return: int

    if first click of game, set cell to 0 and randomizes all mines in a 3x3 around clicked cell. Checks if clicked cell is unexplored
*/
int MineSweeper::clicked(int r, int c, int clickType){

    if(clickType = 1){
        if(firstClick){
            //toggle flag
            firstClick = false;

            //If cell is already 0, ignore
            if(solutionBoard[r][c] == 0) return 1;

            //search 3x3 arround (r,c) for bombs and relocate
            int bombsMoved = 0;
            for(int i = -1; i <= 1 ; i++){
                for(int j = -1 ; j <= 1 ; j++){
                    int ny = r + i;
                    int nx = c + j;
                    //check if ny and nx are in bounds
                    if(ny < 0 || ny >= n || nx < 0 || nx >= m) continue;

                    //if cell contains bomb, move bomb and reasign cell num
                    if(solutionBoard[ny][nx] == 10){
                        //Assume self num is 0
                        int selfValue = 0;
                        ++bombsMoved;

                        //decrease num of surrounding cells
                        for(int r1 = -1 ; r1 <= 1; r1++){
                            for(int c1 = -1 ; c1 <= 1 ; c1++){
                                //check if ny1 and nx1 are in bounds
                                if(r1 == 0 && c1 == 0) continue;
                                int ny1 = ny + r1;
                                int nx1 = nx + c1;
                                if(ny1 < 0 || ny1 >= n || nx1 < 0 || nx1 >= m) continue;

                                //if cell is bomb, increase self value
                                if(solutionBoard[ny1][nx1] == 10){
                                    ++selfValue;
                                //else not bomb, decrease cell value
                                }else{
                                    //std::cout << "Changing (" << ny1 << "," << nx1 << ") " << solutionBoard[ny1][nx1] << " to " << solutionBoard[ny1][nx1] - 1 << std::endl;
                                    solutionBoard[ny1][nx1] -= 1;
                                }
                            }
                        }

                        solutionBoard[ny][nx] = selfValue;
                    }
                }
            }

            std::vector<std::tuple<int, int>> newMines = {};

            while(newMines.size() <= bombsMoved){

                //generate random bomb locations
                int newRow = std::rand() % n;
                int newCol = std::rand() % m;

                //check if in original 3x3
                if(newRow >= r - 1 && newRow <= r + 1 && newCol >= c - 1 && newCol <= c + 1) continue;

                //check if already a bomb location
                if(solutionBoard[newRow][newCol] == 10) continue;

                newMines.push_back(std::make_tuple(newRow,newCol));
            }

            //add mines to board
            setMines(newMines);
        }
        if(board[r][c] != -1) return 0;     //If clicking already visited cell, return fail
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
/*
Functions args: row and col of starting 0 cell
Return: void

Recursively iterates through all adjacent cells with 0
*/
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