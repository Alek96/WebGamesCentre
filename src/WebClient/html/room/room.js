
var room = function (game) {
    console.log("Initialize room");
};

room.prototype = {
    startButton: null,

    preload: function () {
        console.log("Enter room");
    },
    create: function () {
        this.startButton = game.add.button(100, 50, 'TableButton', this.openTable, this, 1, 0, 2);
        this.startButton.anchor.set(0.5);
        this.startButton = game.add.button(75, game.world.height-30, 'BackButton', this.openBack, this, 1, 0, 2);
        this.startButton.anchor.set(0.5);
    },
    update: function () {},
    shutdown: function () {
        console.log("Leave room");
    },

    openTable: function () {
        //alert("Game!!")
        this.startButton = game.add.button(200, game.world.height / 2, 'BackButton', this.openTable, this, 1, 0, 2);
        //loadFile("arkanoid/arkanoid.js", this.open);
    },
    openBack: function () {
        game.state.start('LobbyBoot');
    },
    open: function () {
        game.state.start(state);
    }
}