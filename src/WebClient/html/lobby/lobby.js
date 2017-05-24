
var lobby = function (game) {
    console.log("Initialize lobby");
};

lobby.prototype = {
    i: 0,
    text: '',
    startButton: null,

    preload: function () {
        console.log("Enter lobby");
    },
    create: function () {
        var textStyle = { font: '18px Arial', fill: '#0095DD' };
        this.text = game.add.text(game.world.width - 5, 5, 'i: 0', textStyle);
        this.text.anchor.set(1, 0);
        this.startButton = game.add.button(100, 50, 'arkanoidButton', this.openArkanoid, this, 1, 0, 2);
        this.startButton.anchor.set(0.5);
    },
    update: function () {
        this.i++;
        this.text.setText('i: ' + this.i);
    },
    shutdown: function () {
        console.log("Leave lobby");
    },

    openArkanoid: function () {
        loadFile("room/roomInit.js", callFunction, ['roomInit']);
    }
}