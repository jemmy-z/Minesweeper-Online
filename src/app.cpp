#include <server.h>
#include <TicTacToe.hpp>

using namespace ucm;

int main(int argc, char** argv){

    CrowServer server(argc, argv);

    TicTacToe game;

    server.renderHTML("/", "index.html");

    server.route("/NewGame", [&](const request& req, response& res){

        game.reset();
    
        res.sendHTML("");
    });

    server.route("/cellClicked", [&](const request& req, response& res){
        if (req.has_params({"row", "col"})){

            int row = std::stoi(req.url_params.get("row"));
            int col = std::stoi(req.url_params.get("col"));

            res.sendJSON(game.clicked(row, col));
            
        }
        else{
            res.sendError400();
        } 
    });

    server.route("/updateGrid", [&](const request& req, response& res){

        json response = game.pushGrid();
    
        res.sendJSON(response);
 
    });

    server.run();
}
