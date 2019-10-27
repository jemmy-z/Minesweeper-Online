#include <server.h>
#include <Player.h>
#include <Lobby.hpp>
#include <MineSweeper.hpp>

using namespace minesweeper;

int main(int argc, char** argv){

    CrowServer server(argc, argv);

    lobby mainLobby = lobby();
    int next_index = 0;

    std::tuple<std::string, int> leaderboard[10];

    server.renderHTML("/", "index.html");
    server.renderHTML("/game.html", "game.html");

    server.route("/JoinLobby", [&](const request& req, response& res) {

        Player* p = new Player(next_index);
        minesweeper::json result = mainLobby.joinLobby(p);
        if(result["success"] == 1){   
            result["pid"] = next_index;
            ++next_index;
        }

        res.sendJSON(result);
    });

    server.route("/StartGame", [&](const request& req, response& res) {
        minesweeper::json result;
        mainLobby.startLobby();
        std::tuple<int, int> dimension = mainLobby.getDimensions();
        result["r"] = std::get<0>(dimension);
        result["c"] = std::get<1>(dimension);
        result["numBombs"] = mainLobby.getNumMines();
        res.sendJSON(result);
    });

    server.route("/NewGame", [&](const request& req, response& res){
        //Clear Lobby
        mainLobby = lobby();

        //reset next_index
        next_index = 0;

        res.sendHTML("");
    });

    //recursive end call
    server.route("/StartDelay", [&](const request& req, response& res){     //0 = stop, 1 = play
        minesweeper::json result;
        result["start"] = mainLobby.startable();
        res.sendJSON(result);
    });
  
    server.route("/cellClicked", [&](const request& req, response& res) {
        if (req.has_params({"pid", "row", "col", "clickType"})){

            int PID = std::stoi(req.url_params.get("pid"));
            int row = std::stoi(req.url_params.get("row"));
            int col = std::stoi(req.url_params.get("col"));
            int clickType = std::stoi(req.url_params.get("clickType"));

            MineSweeper *game = mainLobby.getPlayerFromID(PID)->getGame();
            int clickResult = game->clicked(row, col, clickType);

            //1 = left click, 2 = right click
            minesweeper::json result;
            result["groupClear"] = false;
            if(clickResult == 1){

                int value = game->pushCell(row, col);            //Implement group clearing for 0 cell
                if(value == 0){
                    result["groupClear"] = true;
                    game->groupClear(row,col);
                }else{
                    result["value"] = game->pushCell(row, col);
                }
                res.sendJSON(result);
            }else{
                return result;
            }
        }
        else{
            res.sendError400();
        } 
    });

    server.route("/updateGrid", [&](const request& req, response& res){
        if (req.has_params({"pid"})){
            int PID = std::stoi(req.url_params.get("pid"));
            Player* p = mainLobby.getPlayerFromID(PID);
            if(p != NULL){
                MineSweeper *game = p->getGame();
                minesweeper::json result = game->pushBoard();
                res.sendJSON(result);
            }else{
                res.sendError400();
            }
            
        }
        else{
            res.sendError400();
        } 
        
    });

    server.run();
}
