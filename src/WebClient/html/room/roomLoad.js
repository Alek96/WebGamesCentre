
var roomLoad = function (game) {
    console.log("Initialize roomLoad");
};

roomLoad.prototype = {
    preload: function () {
        console.log("Enter roomLoad");
    },
    create: function () {
        game.state.start("Room");
    },
    shutdown: function () {
        console.log("Leave roomLoad");
    }
}