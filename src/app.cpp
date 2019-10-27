#include <server.h>
#include <Player.h>
#include <Lobby.hpp>
#include <MineSweeper.hpp>

using namespace minesweeper;

int MAX_PLAYERS = 1;

int main(int argc, char** argv){

    CrowServer server(argc, argv);

    lobby mainLobby = lobby();
    //Player players[MAX_PLAYERS];
    int next_index = 0;

    server.renderHTML("/", "index.html");

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

    // server.route("/cellClicked", [&](const request& req, response& res) {
    //     if (req.has_params({"row", "col"})){

    //         int row = std::stoi(req.url_params.get("row"));
    //         int col = std::stoi(req.url_params.get("col"));

    //         res.sendJSON(game.clicked(row, col));
            
    //     }
    //     else{
    //         res.sendError400();
    //     } 
    // });

    // server.route("/updateGrid", [&](const request& req, response& res) {

    //     json response = game.pushGrid();
    
    //     res.sendJSON(response);
 
    // });

    server.run();
}
