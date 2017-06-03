
var chessLoad = function (game) {
    console.log("Initialize roomLoad");
};

chessLoad.prototype = {
    preload: function () {
        console.log("Enter roomLoad");

        game.load.image('chessChessboard', 'chess/img/chessboard.png');
        game.load.image('chessPause', 'chess/img/pause.png');

        game.load.image('chessBlackKing', 'chess/img/black_king.png');
        game.load.image('chessBlackQueen', 'chess/img/black_queen.png');
        game.load.image('chessBlackRook', 'chess/img/black_rook.png');
        game.load.image('chessBlackBishop', 'chess/img/black_bishop.png');
        game.load.image('chessBlackKnight', 'chess/img/black_knight.png');
        game.load.image('chessBlackPawn', 'chess/img/black_pawn.png');

        game.load.image('chessWhiteKing', 'chess/img/white_king.png');
        game.load.image('chessWhiteQueen', 'chess/img/white_queen.png');
        game.load.image('chessWhiteRook', 'chess/img/white_rook.png');
        game.load.image('chessWhiteBishop', 'chess/img/white_bishop.png');
        game.load.image('chessWhiteKnight', 'chess/img/white_knight.png');
        game.load.image('chessWhitePawn', 'chess/img/white_pawn.png');

        game.load.image('chessRedBox', 'chess/img/red_box.png');
    },
    create: function () {
        game.state.start("ChessMenu");
    },
    shutdown: function () {
        console.log("Leave roomLoad");
    }
}