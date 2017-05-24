
var roomBoot = function (game) {
    console.log("Initialize roomBoot");
};

roomBoot.prototype = {
    preload: function () {
        console.log("Enter roomBoot");
    },
    create: function () {
        game.state.start("RoomLoad");
    },
    shutdown: function () {
        console.log("Leave roomBoot");
    }
}