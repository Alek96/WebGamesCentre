//chessInit();

var chessInit = function () {
//function chessInit() {
    console.log("Initialize roomInit");
    var NumberOfFilesToLoad = 3;
    var firstState = 'ChessBoot';

    loadFile("chess/chessBoot.js", function () { afterLoading('ChessBoot', 'chessBoot'); });
    loadFile("chess/chessLoad.js", function () { afterLoading('ChessLoad', 'chessLoad'); });
    loadFile("chess/chessMenu.js", function () { afterLoading('ChessMenu', 'chessMenu'); });
    loadFile("chess/chess.js", function () { afterLoading('Chess', 'chess'); });

    function afterLoading(stateName, functionName) {
        addState(stateName, functionName);
        NumberOfFilesToLoad--;
        if (NumberOfFilesToLoad === 0) {
            console.log("Start state: " + firstState);
            this.game.state.start(firstState);
        }
    }
};

var createChessFigure = function (x, y, spriteName, callback, callbackContext) {
    var sprite = game.add.sprite(x * 300, y * 300, spriteName);

    if (callback) {
        sprite.inputEnabled = true;
        sprite.input.useHandCursor = true;

        //run the function only when the pointer is over text
        sprite.events.onInputUp.add(function (sprite) {
            if (!game.paused)
                if (sprite.input.pointerOver())
                    callback.call(callbackContext, sprite);
        }, callbackContext);
    }
    sprite.chessFiguresInfo = callbackContext.createChessFiguresInfo();

    return sprite;
}

var redBox = function (x, y, callback, callbackContext, figureSprite) {
    var sprite = game.add.sprite(x * 300, y * 300, 'chessRedBox');

    if (callback) {
        sprite.inputEnabled = true;
        sprite.input.useHandCursor = true;

        //run the function only when the pointer is over text
        sprite.events.onInputUp.add(function () {
            if (sprite.input.pointerOver())
                callback.call(callbackContext, sprite);
        }, callbackContext);

        if (figureSprite)
            sprite.figureSprite = figureSprite;

        //console.log(sprite.figuresSprite);
    }
    
    return sprite;
}