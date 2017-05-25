
var room = function (game) {
    console.log("Initialize room");
};

room.prototype = {
    parent: null,
    buttonsInfo: {},

    preload: function () {
        console.log("Enter room");
    },
    create: function () {
        this.buttons = game.add.group();
        this.__proto__.parent = this;

        this.buttons.add(TextButton(game.world.width / 8, game.world.height - 30, "Back", this.openBack, this));
        this.buttons.add(TextButton(game.world.width / 2, game.world.height - 30, "New game", this.openNewGame, this));
        this.buttons.add(TextButton(game.world.width * 7 / 8, game.world.height - 30, "Make game", this.openMakeGame, this));
        this.buttons.add(TextButton(100, 50, "TableTest", this.openTest, this));
        this.buttons.add(TextButton(100, 90, "TableTest", this.openTest, this));

        this.buttonsInit();
    },
    update: function () {},
    shutdown: function () {
        console.log("Leave room");
    },

    openTest: function () {
        alert("Test!");
    },
    openBack: function () {
        game.state.start('LobbyBoot');
    },
    openMakeGame: function () {
        room.prototype.addTableButton();
    },
    openNewGame: function () {
        room.prototype.addTableButton();
        room.prototype.openEnterGame();
    },
    openEnterGame: function () {
        loadFile("arkanoid/arkanoidInit.js", callFunction, ['arkanoidInit']);
    },


    buttonsInit: function () {
        this.__proto__.buttonsInfo = {
            width: 100,
            height: 130,
            space: 40
        };
        //Load information from the server and add to the buttons
    },
    addTableButton: function () {
        this.parent.buttons.add(TextButton(100, this.buttonsInfo.height, "Table", this.openEnterGame, this.parent));
        this.buttonsInfo.height += this.buttonsInfo.space;
    }
};