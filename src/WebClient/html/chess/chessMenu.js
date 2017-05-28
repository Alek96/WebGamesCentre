
var chessMenu = function (game) {
    console.log("Initialize room");
};

chessMenu.prototype = {
    parent: null,

    init: function () {
        //
    },
    preload: function () {
        console.log("Enter room");
    },
    create: function () {
        this.buttons = game.add.group();

        this.buttons.add(TextButton(game.world.width / 2, game.world.height * 1 / 8, "Menu", undefined, undefined, { font: '400px Arial', fill: '#black' }));
        this.buttons.add(TextButton(game.world.width / 2, game.world.height * 3 / 8, "Choose color:", undefined, undefined, { font: '200px Arial', fill: '#black' }));

        //this.buttons.add(TextButton(game.world.width * 1 / 4, game.world.height * 5 / 8, "White", this.ChooseWhite, this, { font: '200px Arial', fill: '#black' }));
        //this.buttons.add(TextButton(game.world.width * 3 / 4, game.world.height * 5 / 8, "Black", this.ChooseBlack, this, { font: '200px Arial', fill: '#black' }));

        var button = 0;

        button = game.add.button(game.world.width * 1 / 4, game.world.height * 5 / 8, 'chessWhiteKing', this.ChooseWhite, this);
        button.anchor.set(0.5);
        this.buttons.add(button);

        button = game.add.button(game.world.width * 3 / 4, game.world.height * 5 / 8, 'chessBlackKing', this.ChooseBlack, this);
        button.anchor.set(0.5);
        this.buttons.add(button);
    },
    update: function () {},
    shutdown: function () {
        console.log("Leave room");
    },

    ChooseWhite: function () {
        chess.prototype.getChessboardSpecialInfo = function () {
            var info = {
                atTheBottom: 'White',
                atTheTop: 'Black'
            };
            return info;
        }
        game.state.start("Chess");
    },
    ChooseBlack: function () {
        chess.prototype.getChessboardSpecialInfo = function () {
            var info = {
                atTheBottom: 'Black',
                atTheTop: 'White'
            };
            return info;
        }
        game.state.start("Chess");
    }
};