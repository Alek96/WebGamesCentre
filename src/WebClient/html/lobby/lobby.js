
var lobby = function (game) {
    console.log("Initialize lobby");
};

lobby.prototype = {
    i: 0,
    text: '',
    buttons: null,

    preload: function () {
        console.log("Enter lobby");
    },
    create: function () {
        this.buttons = game.add.group();

        this.buttons.add(TextButton(game.world.width / 2, 100, 'WebGamesCentre', undefined, undefined, { font: '80px Arial', fill: '#black' }));

        this.buttons.add(TextButton(game.world.width / 2, game.world.height * 3 / 8, "Arkanoid", this.openArkanoid, this));
        this.buttons.add(TextButton(game.world.width / 2, game.world.height * 5 / 8, "Chess", this.openChess, this));

        var textStyle = { font: '18px Arial', fill: '#0095DD' };
        this.text = game.add.text(game.world.width - 5, 5, 'i: 0', textStyle);
        this.text.anchor.set(1, 0);
    },
    update: function () {
        this.i++;
        this.text.setText('i: ' + this.i);
    },
    shutdown: function () {
        console.log("Leave lobby");
    },

    openArkanoid: function () {
        loadFile("room/roomInit.js", callFunction, ['roomInit', 'Arkanoid']);
    },
    openChess: function () {
        loadFile("room/roomInit.js", callFunction, ['roomInit', 'Chess']);
    }
};