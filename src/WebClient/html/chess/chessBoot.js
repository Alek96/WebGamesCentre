
var chessBoot = function (game) {
    console.log("Initialize roomBoot");
};

chessBoot.prototype = {
    preload: function () {
        console.log("Enter roomBoot");
    },
    create: function () {
        game.scale.setGameSize(2400, 2400);
        game.scale.scaleMode = Phaser.ScaleManager.SHOW_ALL;
        game.scale.pageAlignHorizontally = true;
        game.scale.pageAlignVertically = true;
        game.scale.refresh();
        game.stage.backgroundColor = '#eee';

        game.state.start("ChessLoad");
    },
    shutdown: function () {
        console.log("Leave roomBoot");
    }
}