
var lobbyBoot = function (game) {
    console.log("Initialize lobbyBoot");
};

lobbyBoot.prototype = {
    preload: function () {
        console.log("Enter lobbyBoot");
    },
    create: function () {
        game.scale.setGameSize(1280, 720);
        game.scale.scaleMode = Phaser.ScaleManager.SHOW_ALL;
        game.scale.pageAlignHorizontally = true;
        game.scale.pageAlignVertically = true;
        game.scale.refresh();
        //this.scale.setScreenSize();
        game.stage.backgroundColor = '#eee';
        game.state.start("LobbyLoad");
    },
    shutdown: function () {
        console.log("Leave lobbyBoot");
    }
}