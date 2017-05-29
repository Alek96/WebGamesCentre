
var room = function (game) {
    console.log("Initialize room");
};

room.prototype = {
    parent: null,
    buttonsInfo: {},

    init: function () {
        this.__proto__.buttonsInfo = {
            width: 200,
            height: 160,
            space: 40
        };
    },
    preload: function () {
        console.log("Enter room");
    },
    create: function () {
        this.buttons = game.add.group();
        this.__proto__.parent = this;
        //this.__proto__.gameName = lobby.__proto__.gameName;
        this.buttons.add(TextButton(game.world.width / 2, 80, "Chess", undefined, undefined, { font: '80px Arial', fill: '#black' }));

        this.buttons.add(TextButton(game.world.width / 8, game.world.height - 30, "Back", this.openBack, this));
        this.buttons.add(TextButton(game.world.width / 2, game.world.height - 30, "New game", this.openNewGame, this));
        this.buttons.add(TextButton(game.world.width * 7 / 8, game.world.height - 30, "Create game", this.openMakeGame, this));

        this.buttons.add(TextButton(this.__proto__.buttonsInfo.width, this.__proto__.buttonsInfo.height, "TableTest", this.openTest, this));
        this.__proto__.buttonsInfo.height += this.__proto__.buttonsInfo.space;
        this.buttons.add(TextButton(this.__proto__.buttonsInfo.width, this.__proto__.buttonsInfo.height, "TableTest", this.openTest, this));
        this.__proto__.buttonsInfo.height += this.__proto__.buttonsInfo.space;

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
        loadFile("chess/chessInit.js", callFunction, ['chessInit']);
    },


    buttonsInit: function () {
        //Load information from the server and add to the buttons
    },
    addTableButton: function () {
        this.parent.buttons.add(TextButton(this.buttonsInfo.width, this.buttonsInfo.height, "Table", this.openEnterGame, this.parent));
        this.buttonsInfo.height += this.buttonsInfo.space;
    }
};