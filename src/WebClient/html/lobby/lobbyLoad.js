
var lobbyLoad = function (game) {
    console.log("Initialize lobbyLoad");
};

lobbyLoad.prototype = {
    preload: function () {
        console.log("Enter lobbyLoad");
    },
    create: function () {
        game.state.start("Lobby");
    },
    shutdown: function () {
        console.log("Leave lobbyBoot");
    }
}