#include <TicTacToe.hpp>
#include <algorithm>
#include <iostream>

TicTacToe::TicTacToe(){
    init();
}

void TicTacToe::init(){
    grid = new int*[3];
    for(int r = 0 ; r < 3 ; r++){
		grid[r] = new int[3];
		for(int c = 0 ; c < 3 ; c++){
			grid[r][c] = 0;
		}
	}
    currentPlayer = 1;
}

void TicTacToe::setJoinable(bool b){
    joinable = true;
    joinCode = codeGen();
    std::cout << joinCode << std::endl;
}

void TicTacToe::reset(){
    for(int r = 0 ; r < 3 ; r++){
		for(int c = 0 ; c < 3 ; c++){
			grid[r][c] = 0;
		}
	}
    currentPlayer = 1;
    acceptClicks = true;
}

ucm::json TicTacToe::pushGrid(){
    ucm::json result;
    for(int r = 0 ; r < 3 ; r++){
		std::vector<int> fin = {};
		for (int c = 0 ; c < 3 ; c++){
			fin.push_back(grid[r][c]);
 		}
		result.push_back(fin);
	}
    return result;
}

ucm::json TicTacToe::clicked(int r, int c){
    /* Json return results
        1 = player 1 wins
        -1 = player 2 wins
        0 = continue game
        else
    */
    ucm::json result;
    result["winner"] = 0;
    if(acceptClicks){
        if (grid[r][c] == 0){
            grid[r][c] = currentPlayer;
            int winner = checkWinCondition();
            if(winner != 0){
                result["winner"] = winner;
                acceptClicks = false;
                return result;
            }
            currentPlayer *= -1;
        }
        //Check for draw
        if (drawCondition()){
            result["winner"] = 418;
            acceptClicks = false;
        } 
    }
    return result;
}

int TicTacToe::codeGen(){
    return std::rand() % 9000 + 1000;
}

int TicTacToe::checkWinCondition(){
    for(int i = 0 ; i < 3 ; i++){
        //Check row I
        int rowSum = 0;
        //Check col I
        int colSum = 0;
        for(int j = 0 ; j < 3 ; j++){
            rowSum += grid[i][j];
            colSum += grid[j][i];
        }
        if(rowSum == 3 || colSum == 3){
            return 1;
        }else if(rowSum == -3 || colSum == -3){
            return -1;
        }
    }
    //Check Diagonals
    int forwardSum = 0;
    int backwardSum = 0;
    for(int i = 0 ; i < 3 ; i++){
        forwardSum += grid[i][i];
        backwardSum += grid[i][2 - i];
    }
    if(forwardSum == 3 || backwardSum == 3){
        return 1;
    }else if(forwardSum == -3 || backwardSum == -3){
        return -1;
    }

    return 0;
}

bool TicTacToe::drawCondition(){
    for (int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3; j++){
            if (grid[i][j] == 0) return false;
        }
    }
    return true;
}