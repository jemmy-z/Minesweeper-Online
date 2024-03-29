//Init grid and sets .click functions
function createGrid(data){
	var result = "";

	for (var i = 0 ; i < data[0] ; i++){
		var cr = "<tr>";
		for (var j = 0 ; j < data[1] ; j++){   
			cr = cr + "<td class='value0' id=\"" + i.toString() + "-" + j.toString() + "\"></td>"
		}
		cr = cr + "</tr>\n";
		result = result + cr;
	}

    $("#grid").html(result);
    
    for(var i = 0 ; i < data[0] ; i++){
        for(var j = 0 ; j < data[1] ;j++){
            var sel = "#" + i.toString()+ "-" + j.toString();
            $(sel).click(cellClicked).contextmenu(cellClicked);
            $(sel)[0].r = i;
            $(sel)[0].c = j;
        }
    }
}

//calls /cellClicked endpoint and updatesGrid
function cellClicked(event){
    event.preventDefault(); // prevent right-click context menu
    $.get("/cellClicked", {pid: window.pid, row: this.r, col: this.c, clickType: event.which}, function(response){
        var data = JSON.parse(response);
        if(data["groupClear"]){             //If cell clicked == 0 cell, update all cells
            updateGrid(window.pid);
        }
        else if (data["value"]!==void(0)) {         // else update single cell if given a value
            var value = data["value"];      //0-8 = num, 10 == bomb, flag == 10
            var r = data["row"];
            var c = data["col"];
            // set cell value
            var id =  r.toString() + "-" + c.toString();
            $("#"+id).text(value).removeClass().addClass("value"+value)
        }
    });
}

//Calls /updateGrid Endpoint
function updateGrid(){
    $.get("/updateGrid", {pid: window.pid}, function(response){
		var data = JSON.parse(response);
		for (var row in data){
			for (var col in data[row]){
                var sel = "#" + row.toString()+ "-" + col.toString();
                var value = data[row][col];
                $(sel).text(value).removeClass().addClass("value"+value);
			}
		}
    });
}

function startGame() {
    window.pid = parseInt(document.getElementById("pid").classList.item(0));
    $.get("/StartGame", {}, function(response){
        var parsed = JSON.parse(response);
        var r = parsed["r"];
        var c = parsed["c"];
        window.num_bombs = parsed["numBombs"].toString();
        document.getElementById("num-bombs").innerHTML = window.num_bombs;
        createGrid([r, c]);
        updateGrid();
    });
}
function on(pid) {
    document.getElementById("overlay").style.display = "block";
    var count = 3;
    document.getElementById("text").innerHTML = count.toString();
    var x = setInterval(counter, 1000);
    function counter() {
        if (count == 0) {
            clearInterval(x);
            window.location.href="game.html?pid=" + pid;
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

function wait(pid) {
    $.get("/StartDelay", {}, function(response){
        var parsed = JSON.parse(response);
        var start = parseInt(parsed["start"]);
        // document.write(start);
        if (start == 1) {
            on(pid);
        } else {
            setTimeout(wait(), 500);
        }
    });
}

$(document).ready(function(){

    // createGrid();
    //var pid;
    
    $("#JoinLobbyBtn").click(function(){
        $.get("/JoinLobby", {}, function(response){
            var parsed = JSON.parse(response);
            var success = parseInt(parsed["success"]);
            if (success == 0) {
                // on();
                off();
            } else {
                window.pid = parseInt(parsed["pid"]);
                document.getElementById("JoinLobbyBtn").style.display="none";
                document.getElementById("WaitLobbyBtn").style.display="inline";
                wait(pid);
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
