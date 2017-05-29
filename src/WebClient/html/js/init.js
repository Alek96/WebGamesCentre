// Create new game
var game = new Phaser.Game(800, 600, Phaser.AUTO, 'gameDev');

// List of files already added
var filesAdded = "";

function loadFile(url, callback, param) {
    // If the file has not been loaded yet
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

// Function which calls another function. The first parameter is a function name, the rest is arguments
function callFunction(param) {
    if (!Array.isArray(param))
        window[param];
    else
        window[param[0]](param[1], param[2], param[3], param[4], param[5]);
}

// List of state already added
var stateAdded = "";

function addState(stateName, functionName) {
    if (stateAdded.indexOf("[" + stateName + "]") == -1) {
        stateAdded += "[" + stateName + "]";
        game.state.add(stateName, window[functionName]);
        console.log("Add state: " + stateName);
    }
}

// Button with label on it
var LabelButton = function (game, x, y, key, label, callback, callbackContext, overFrame, outFrame, downFrame, upFrame) {
    Phaser.Button.call(this, game, x, y, key, callback, callbackContext, overFrame, outFrame, downFrame, upFrame);
    // Style  
    this.style = { 'font': '26px Arial', 'fill': 'black' };
    this.anchor.setTo(0.5, 0.5);
    this.label = new Phaser.Text(game, 0, 0, label, this.style);
    // Puts the label in the center of the button    
    this.label.anchor.setTo(0.5, 0.5);
    this.addChild(this.label);
    this.setLabel(label);
    // Adds button to game    
    game.add.existing(this);
};
LabelButton.prototype = Object.create(Phaser.Button.prototype);
LabelButton.prototype.constructor = LabelButton;
LabelButton.prototype.setLabel = function (label) {
    this.label.setText(label);
};//np. this.btnStart = new LabelButton(this.game, 480, 512, "buttonsprite", "Start game!", this.doBtnStartHandler, this, 1, 0, 2);

// Text that acts like a button
var TextButton = function (x, y, text, callback, callbackContext, textStyle) {
    var style = (textStyle == undefined ? { font: '40px Arial', fill: '#black' } : textStyle);
    var text = game.add.text(x, y, text, style);
    text.anchor.set(0.5, 0.5);
    if (callback) {
        text.inputEnabled = true;
        text.input.useHandCursor = true;

        // Run the function only when the pointer is over text
        text.events.onInputUp.add(function (arg) {
            if (text.input.pointerOver())
                callback.call(callbackContext, arg);
        }, callbackContext);

        // Add shadow
        text.events.onInputOut.add(function () { text.setShadow(0, 0, 'rgba(0,0,0,0.5)', 0); }, callbackContext);
        text.events.onInputOver.add(function () { text.setShadow(2, 2, 'rgba(0,0,0,0.5)', 5); }, callbackContext);
        text.events.onInputDown.add(function () { text.setShadow(2, 2, 'rgba(0,0,0,0.5)', 10); }, callbackContext);
    }

    return text;
}