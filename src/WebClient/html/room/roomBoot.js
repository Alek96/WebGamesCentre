
var roomBoot = function (game) {
    console.log("Initialize roomBoot");
};

roomBoot.prototype = {
    preload: function () {
        console.log("Enter roomBoot");
    },
    create: function () {
        game.scale.setGameSize(1280, 720);
        game.scale.scaleMode = Phaser.ScaleManager.SHOW_ALL;
        game.scale.pageAlignHorizontally = true;
        game.scale.pageAlignVertically = true;
        game.scale.refresh();
        game.stage.backgroundColor = '#eee';

        game.state.start("RoomLoad");
    },
    shutdown: function () {
        console.log("Leave roomBoot");
    }
}