//set cell text at r,c with state
function updateCell(r, c, state){
    var sel = "#" + r.toString()+ "-" + c.toString();
    
	if (state == 0){
		$(sel).text(" ");
	}else if(state == 1){
		$(sel).text("O");
	}else{
        $(sel).text("X")
    }
}

//Init grid and sets .click functions
function createGrid(data){
	var result = "";

	for (var i = 0 ; i < 3 ; i++){
		var cr = "<tr>";
		for (var j = 0 ; j < 3 ; j++){   
			cr = cr + "<td id=\"" + i.toString() + "-" + j.toString() + "\"></td>"
		}
		cr = cr + "</tr>\n";
		result = result + cr;
	}

    $("#grid").html(result);
    
    for(var i = 0 ; i < 3 ; i++){
        for(var j = 0 ; j < 3 ;j++){
            var sel = "#" + i.toString()+ "-" + j.toString();
            $(sel).click(cellClicked);
            $(sel)[0].r = i;
            $(sel)[0].c = j;
        }
    }
}

//calls /cellClicked endpoint and updatesGrid
function cellClicked(){
    $.get("/cellClicked", {row: this.r, col: this.c}, function(response){
        var data = JSON.parse(response);
        var winner = data.winner;
        if (winner == 1){
            $("#lol").text("Player 1 Wins");
        }else if (winner == -1){
            $("#lol").text("Player 2 Wins");
        }else if (winner == 418){
            $("#lol").text("Draw");
        }
        updateGrid();
    });
}

//Calls /updateGrid Endpoint
function updateGrid(){
    $.get("/updateGrid", {}, function(response){
		var data = JSON.parse(response);
		for (var row in data){
			for (var col in data[row]){
                updateCell(row, col, data[row][col]);
			}
		}
    });
}

$(document).ready(function(){

    createGrid();    
    
    $("#NewGameBtn").click(function(){
        $.get("/NewGame", {}, function(response){
            updateGrid();
            $("#lol").text("Tic Tac Toe");
        });
        
	});
});
