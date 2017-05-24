
var lobbyLoad = function (game) {
    console.log("Initialize lobbyLoad");
};

lobbyLoad.prototype = {
    preload: function () {
        console.log("Enter lobbyLoad");
        game.load.spritesheet('arkanoidButton', 'img/arkanoidButton.png', 120, 40);
    },
    create: function () {
        game.state.start("Lobby");
    },
    shutdown: function () {
        console.log("Leave lobbyBoot");
    }
}