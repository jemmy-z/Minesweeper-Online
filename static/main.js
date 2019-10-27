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

	for (var i = 0 ; i < data[0] ; i++){
		var cr = "<tr>";
		for (var j = 0 ; j < data[1] ; j++){   
			cr = cr + "<td class=\"content\" id=\"" + i.toString() + "-" + j.toString() + "\"></td>"
		}
		cr = cr + "</tr>\n";
		result = result + cr;
	}

    $("#grid").html(result);
    
    for(var i = 0 ; i < data[0] ; i++){
        for(var j = 0 ; j < data[1] ;j++){
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

function startGame() {
    createGrid([20, 35]);
}

function on() {
    document.getElementById("overlay").style.display = "block";
    var count = 3;
    document.getElementById("text").innerHTML = count.toString();
    var x = setInterval(counter, 1000);
    function counter() {
        if (count == 0) {
            clearInterval(x);
            window.location.href="game.html";
        } else {
            count--;
            document.getElementById("text").innerHTML = count.toString();  
        }
    }
}

function off() {
    document.getElementById("text").innerHTML = "";
    document.getElementById("overlay").style.display = "none";
    document.getElementById("JoinLobbyBtn").style.display="inline";
    document.getElementById("WaitLobbyBtn").style.display="none";
}

function wait() {
    $.get("/StartDelay", {}, function(response){
        var parsed = JSON.parse(response);
        var start = parseInt(parsed["start"]);
        // document.write(start);
        if (start == 1) {
            on();
        } else {
            setTimeout(wait(), 500);
        }
    });
}

$(document).ready(function(){

    // createGrid();
    var pid;
    
    $("#JoinLobbyBtn").click(function(){
        $.get("/JoinLobby", {}, function(response){
            var parsed = JSON.parse(response);
            var success = parseInt(parsed["success"]);
            if (success == 0) {
                // on();
                off();
            } else {
                pid = parseInt(parsed["pid"]);
                document.getElementById("JoinLobbyBtn").style.display="none";
                document.getElementById("WaitLobbyBtn").style.display="inline";
                wait();
            }
        });
	});

    $("#StartGameBtn").click(function() {
        $.get("/StartGame", {}, function(response){
            //countdown
            on();
        });
    });
});
