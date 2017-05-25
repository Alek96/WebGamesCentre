
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

        this.buttons.add(TextButton(200, 50, "Arkanoid - TextButton", this.openArkanoid, this));
        this.buttons.add(new LabelButton(game, 200, 90, "ButtonBackground", "Arkanoid - LabelButton", this.openArkanoid, this));

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
        loadFile("room/roomInit.js", callFunction, ['roomInit']);
    }
};