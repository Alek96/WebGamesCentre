
var chess = function (game) {
    console.log("Initialize room");
};

chess.prototype = {
    parent: null,

    init: function () {
        this.__proto__.parent = this;
        if (!this.getChessboardSpecialInfo) {
            this.chessboardSpecialInfo = {
                atTheBottom: 'White',
                atTheTop: 'Black'
            };
        }
        else {
            this.chessboardSpecialInfo = this.getChessboardSpecialInfo();
        }
    },
    preload: function () {
        console.log("Enter room");
    },
    create: function () {
        game.add.sprite(0 * 300, 0 * 300, 'chessChessboard');

        this.chessFigures = game.add.group();
        this.redBoxs = game.add.group();
        this.buttons = game.add.group();
        this.menu = game.add.group();

        var button = game.add.button(game.world.width - 150, 50, 'chessPause', function () { game.paused = true; }, this);
        button.anchor.set(0.5);
        this.buttons.add(button);

        this.initFigures();
        this.initMenu();
    },
    update: function () {},
    shutdown: function () {
        console.log("Leave room");
    },
    paused: function () {
        this.menu.visible = true; // show menu
    },
    pauseUpdate: function () {
        console.log("pause");
    },
    initMenu: function () {
        var rect = game.add.graphics(0, 0);
        rect.beginFill(0x000000, 0.75); // color-white, alpha
        rect.boundsPadding = 0;
        rect.drawRect(0, 0, game.world.width, game.world.height);
        this.menu.add(rect);

        rect = game.add.graphics(0, 0);
        rect.beginFill(0xDDDDDD, 1); // color-grey, alpha
        rect.boundsPadding = 0;
        var paddingX = 2 * 300;
        var paddingY = 2 * 300;
        rect.drawRect(paddingX, paddingY, game.world.width - paddingX * 2, game.world.height - paddingY * 2);
        this.menu.add(rect);

        this.menu.add(TextButton(game.world.width / 2, game.world.height * 3 / 8, "Resume", this.resume, this, { font: '200px Arial', fill: '#black' }));
        this.menu.add(TextButton(game.world.width / 2, game.world.height * 4 / 8, "New Game", this.newGame, this, { font: '200px Arial', fill: '#black' }));
        this.menu.add(TextButton(game.world.width / 2, game.world.height * 5 / 8, "Exit", this.exit, this, { font: '200px Arial', fill: '#black' }));

        this.menu.visible = false; // hide menu
    },
    resume: function () {
        this.menu.visible = false; // hide menu
        game.paused = false;
    },
    newGame: function () {
        this.menu.visible = false; // hide menu
        game.paused = false;
        game.state.start("ChessMenu");
    },
    exit: function () {
        this.menu.visible = false; // hide menu
        game.paused = false;
        game.state.start("RoomBoot");
    },
    
    createChessFiguresInfo: function () {
        var chessFiguresInfo = {
            firstMove: true,
            check: false
        };
        return chessFiguresInfo;
    },
    initFigures: function () {
        if (this.chessboardSpecialInfo.atTheBottom == 'White') {
            this.chessboardInfo = [
                ['BlackRook', 'BlackKnight', 'BlackBishop', 'BlackQueen', 'BlackKing', 'BlackBishop', 'BlackKnight', 'BlackRook'],
                ['BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn'],
                [, , , , , , ,],
                [, , , , , , ,],
                [, , , , , , ,],
                [, , , , , , ,],
                ['WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn'],
                ['WhiteRook', 'WhiteKnight', 'WhiteBishop', 'WhiteQueen', 'WhiteKing', 'WhiteBishop', 'WhiteKnight', 'WhiteRook'],
            ];
        }
        else {
            this.chessboardInfo = [
                ['WhiteRook', 'WhiteKnight', 'WhiteBishop', 'WhiteKing', 'WhiteQueen', 'WhiteBishop', 'WhiteKnight', 'WhiteRook'],
                ['WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn', 'WhitePawn'],
                [, , , , , , ,],
                [, , , , , , ,],
                [, , , , , , ,],
                [, , , , , , ,],
                ['BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn', 'BlackPawn'],
                ['BlackRook', 'BlackKnight', 'BlackBishop', 'BlackKing', 'BlackQueen', 'BlackBishop', 'BlackKnight', 'BlackRook'],
            ];
        }

        for (var i = 0; i < 8; i++) {
            for (var j = 0; j < 8; j++) {
                if (this.isExist(j,i))
                    this.chessFigures.add(createChessFigure(j, i, 'chess' + this.chessboardInfo[i][j], this.addRedBoxs, this));
            }
        }
    },
    addRedBoxs: function (sprite) {
        if (sprite.key.substring(5, 10) == this.chessboardSpecialInfo.atTheBottom) { // (5-10) = White/Black 
            this.redBoxs.removeAll(true, false);    //erase all red box
            var funName = 'move' + sprite.key.slice(10); //5-chess + 5-White/Black
            //console.log(funName);
            this[funName](sprite);
        }
    },
    movePawn: function (sprite) {
        var x = sprite.world.x / 300;
        var y = sprite.world.y / 300;
        var name = sprite.key;

        if (this.isExist(x, y - 1) === false) {
            this.redBoxs.add(redBox(x, y - 1, this.setAndMove, this, sprite));

            if (sprite.chessFiguresInfo.firstMove == true) {
                if (this.isExist(x, y - 2) === false)
                    this.redBoxs.add(redBox(x, y - 2, this.setAndMove, this, sprite));
            }
        }

        if (this.isEnemy(x - 1, y - 1))
            this.redBoxs.add(redBox(x - 1, y - 1, this.setAndMove, this, sprite));

        if (this.isEnemy(x + 1, y - 1))
            this.redBoxs.add(redBox(x + 1, y - 1, this.setAndMove, this, sprite));
    },
    moveKnight: function (sprite) {
        //upper left boxs
        this.addRedBoxsQuarterBoard(sprite, 'up', 'left');

        //upper right boxs
        this.addRedBoxsQuarterBoard(sprite, 'up', 'right');

        //button left boxs
        this.addRedBoxsQuarterBoard(sprite, 'down', 'left');

        //button right boxs
        this.addRedBoxsQuarterBoard(sprite, 'down', 'right');
    },
    addRedBoxsQuarterBoard: function (figureSprite, verticalDirection, horizontalDirection) {
        var x = figureSprite.world.x / 300;
        var y = figureSprite.world.y / 300;
        var i = 0;
        var vertical = 1;
        var horizontal = 1;

        if (verticalDirection == 'up')
            var vertical = -1;
        if (horizontalDirection == 'left')
            var horizontal = -1;

        if (this.isExist(x + 1 * horizontal, y + 2 * vertical) === false ||
            this.isEnemy(x + 1 * horizontal, y + 2 * vertical) === true) 
            this.redBoxs.add(redBox(x + 1 * horizontal, y + 2 * vertical, this.setAndMove, this, figureSprite));

        if (this.isExist(x + 2 * horizontal, y + 1 * vertical) === false ||
            this.isEnemy(x + 2 * horizontal, y + 1 * vertical) === true)
            this.redBoxs.add(redBox(x + 2 * horizontal, y + 1 * vertical, this.setAndMove, this, figureSprite));
    },
    moveBishop: function (sprite) {
        //upper left boxs
        this.addRedBoxsLine(sprite, 'up', 'left');

        //upper right boxs
        this.addRedBoxsLine(sprite, 'up', 'right');

        //button left boxs
        this.addRedBoxsLine(sprite, 'down', 'left');

        //button right boxs
        this.addRedBoxsLine(sprite, 'down', 'right');
        
    },
    moveRook: function (sprite) {
        //upper boxs
        this.addRedBoxsLine(sprite, 'up', '');

        //button boxs
        this.addRedBoxsLine(sprite, 'down', '');

        //left boxs
        this.addRedBoxsLine(sprite, '', 'left');

        //upper boxs
        this.addRedBoxsLine(sprite, '', 'right');
    },
    moveQueen: function (sprite) {
        //upper boxs
        this.addRedBoxsLine(sprite, 'up', '');

        //button boxs
        this.addRedBoxsLine(sprite, 'down', '');

        //left boxs
        this.addRedBoxsLine(sprite, '', 'left');

        //upper boxs
        this.addRedBoxsLine(sprite, '', 'right');

        //upper left boxs
        this.addRedBoxsLine(sprite, 'up', 'left');

        //upper right boxs
        this.addRedBoxsLine(sprite, 'up', 'right');

        //button left boxs
        this.addRedBoxsLine(sprite, 'down', 'left');

        //button right boxs
        this.addRedBoxsLine(sprite, 'down', 'right');
    },
    addRedBoxsLine: function (figureSprite, verticalDirection, horizontalDirection) {
        var x = figureSprite.world.x / 300;
        var y = figureSprite.world.y / 300;
        var i = 0;
        var vertical = 0;
        var horizontal = 0;

        if (verticalDirection == 'up')
            var vertical = -1;
        if (verticalDirection == 'down')
            var vertical = 1;
        if (horizontalDirection == 'left')
            var horizontal = -1;
        if (horizontalDirection == 'right')
            var horizontal = 1;

        for (i = 1; i < 8; i++) {
            if (this.isExist(x + i * horizontal, y + i * vertical) === false)
                this.redBoxs.add(redBox(x + i * horizontal, y + i * vertical, this.setAndMove, this, figureSprite));
            else {
                if (this.isEnemy(x + i * horizontal, y + i * vertical) === true)
                    this.redBoxs.add(redBox(x + i * horizontal, y + i * vertical, this.setAndMove, this, figureSprite));
                break;
            }
        }
    },
    moveKing: function (sprite) {
        var x = sprite.world.x / 300;
        var y = sprite.world.y / 300;

        for (var i = -1; i <= 1; i++)
            for (var j = -1; j <= 1; j++)
                if (i != 0 || j != 0) {
                    if (this.isExist(x + j, y + i) === false)
                        this.redBoxs.add(redBox(x + j, y + i, this.setAndMove, this, sprite));
                    else if (this.isEnemy(x + j, y + i) === true)
                        this.redBoxs.add(redBox(x + j, y + i, this.setAndMove, this, sprite));
                }
    },
    isExist: function (x, y) {
        if (y < 0 || x < 0 || y >= 8 || x >= 8) //if it is out of the chessboard 
            return undefined;
        else if (this.chessboardInfo[y][x] && this.chessboardInfo[y][x] != '') //if it is not exist  
            return true;
        else
            return false;
    },
    isEnemy: function (x, y) {
        if (this.isExist(x, y))
            if (this.chessboardInfo[y][x].substring(0, 5) == this.chessboardSpecialInfo.atTheTop) //it is enemy
                return true;
        return false;
    },
    setAndMove: function (sprite) {
        var x = sprite.world.x / 300;
        var y = sprite.world.y / 300;
        var figureSprite = sprite.figureSprite;
        
        this.move(figureSprite, x, y);

        if (figureSprite.chessFiguresInfo.firstMove)
            figureSprite.chessFiguresInfo.firstMove = false;

        this.redBoxs.removeAll(true, false);    //erase all red box
    },
    move: function (sprite, x, y) {
        var oldX = sprite.world.x / 300;
        var oldY = sprite.world.y / 300;

        this.chessboardInfo[oldY][oldX] = '';
        this.chessboardInfo[y][x] = sprite.key.slice(5);

        sprite.x = x * 300;
        sprite.y = y * 300;
    }
};