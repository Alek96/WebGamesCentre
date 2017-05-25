
var lobbyLoad = function (game) {
    console.log("Initialize lobbyLoad");
};

lobbyLoad.prototype = {
    preload: function () {
        console.log("Enter lobbyLoad");
        game.load.spritesheet('ButtonBackground', 'img/ButtonBackground.png', 20, 20);
    },
    create: function () {
        game.state.start("Lobby");
    },
    shutdown: function () {
        console.log("Leave lobbyBoot");
    }
}