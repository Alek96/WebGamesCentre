
var roomLoad = function (game) {
    console.log("Initialize roomLoad");
};

roomLoad.prototype = {
    preload: function () {
        console.log("Enter roomLoad");
        game.load.spritesheet('TableButton', 'img/TableButton.png', 120, 40);
        game.load.spritesheet('BackButton', 'img/BackButton.png', 150, 50);
    },
    create: function () {
        game.state.start("Room");
    },
    shutdown: function () {
        console.log("Leave roomLoad");
    }
}