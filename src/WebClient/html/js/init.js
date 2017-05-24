//make new game
var game = new Phaser.Game(480, 320, Phaser.AUTO, 'gameDev');

//list of files already added
var filesAdded = "";

function loadFile(url, callback, param) {
    // if the file has not been loaded yet
    if (filesAdded.indexOf("[" + url + "]") == -1) {
        filesAdded += "[" + url + "]";

        var script = document.createElement('script');
        script.setAttribute("type", "text/javascript");
        script.setAttribute("src", url);

        //document.getElementsByTagName('head')[0].appendChild(script);
        document.head.appendChild(script);

        if (callback) {
            script.onreadystatechange = function () { callback(param); };
            script.onload = function () { callback(param); };
        }

        console.log("Load " + url);
    }
    else {
        if (callback)
            callback(param);
    }
}

function callFunction(param) {
    if (!Array.isArray(param))
        window[param];
    else
        window[param[0]](param[1], param[2], param[3], param[4], param[5]);
}

function addState(stateName, functionName, startState = false) {
    game.state.add(stateName, window[functionName]);
    console.log("Add state: " + stateName);
    if (startState == true) {
        game.state.start(stateName);
        console.log("Start state: " + stateName);
    }
}