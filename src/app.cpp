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
    //server.renderHTML("/game.html", "game.html");

    server.route("/JoinLobby", [&](const request& req, response& res) {

        Player p = Player(next_index);
        minesweeper::json result = mainLobby.joinLobby(p);
        if(result["success"] == 1){   
            result["pid"] = next_index;
            ++next_index;
        }

        res.sendJSON(result);
    });

    server.route("/StartGame", [&](const request& req, response& res) {
        int PID = std::stoi(req.url_params.get("pid"));
        if(PID == 0){
            mainLobby.startLobby();
        }
        res.sendHTML("");
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
            minesweeper::json result;

            int PID = std::stoi(req.url_params.get("pid"));
            int row = std::stoi(req.url_params.get("row"));
            int col = std::stoi(req.url_params.get("col"));
            int clickType = std::stoi(req.url_params.get("clickType"));


            MineSweeper game = mainLobby.getPlayerFromID(PID).getGame();
            int clickResult = game.clicked(row, col, clickType);

            if(clickResult == 1){

                int value = game.pushCell(row, col);            //Implement group clearing for 0 cell
                
                if(value == 0){
                    result = game.groupClear(row, col);
                }else{
                    result["row"] = row;
                    result["col"] = col;
                    result["value"] = game.pushCell(row, col);
                }
                res.sendJSON(result);
            }else{
                res.sendHTML("");
            }
        }
        else{
            res.sendError400();
        } 
    });

    server.run();
}
