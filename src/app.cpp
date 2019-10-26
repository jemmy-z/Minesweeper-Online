#include <server.h>
#include <Player.h>
#include <MineSweeper.hpp>

using namespace minesweeper;

int MAX_PLAYERS = 1;


int main(int argc, char** argv){

    CrowServer server(argc, argv);

    //MineSweeper gameboards[MAX_PLAYERS];
    Player players[MAX_PLAYERS];
    int next_index = 0;


    server.renderHTML("/", "index.html");

    server.route("/JoinGame", [&](const request& req, response& res) {
        assert (next_index < MAX_PLAYERS);
        players[next_index] = Player(next_index);
        next_index++;

        res.sendHTML("");
    });

    server.route("/StartGame", [&](const request& req, response& res) {
        assert (sizeof(players) > 1);
        // disable NewGame

        // initialize gameboard

        // copy gameboard to list of gameboards

        // countdown from 3
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
