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

function on() {
    document.getElementById("overlay").style.display = "block";
    var count = 3;
    document.getElementById("text").innerHTML = count.toString();
    var x = setInterval(counter, 1000);
    function counter() {
        if (count == 0) {
            clearInterval(x);
            off();
        } else {
            count--;
            document.getElementById("text").innerHTML = count.toString();  
        }
    }
}

function off() {
  document.getElementById("text").innerHTML = "";
  document.getElementById("overlay").style.display = "none";
}

function wait() {
    $.get("/StartDelay", {}, function(response){
        var start = parseInt(response["start"]);
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
            var success = parseInt(response["success"]);
            if (success == 0) {
                off();
            } else {
                pid = parseInt(response["pid"]);
                document.getElementById("JoinLobbyBtn").innerHTML = "Waiting in Lobby";
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
