
var roomInit = function (game) {
    console.log("Initialize roominit");

    loadFile("room/roomLoad.js", callFunction, ['addState', 'RoomLoad', 'roomLoad']);
    loadFile("room/room.js", callFunction, ['addState', 'Room', 'room']);
    loadFile("room/roomBoot.js", callFunction, ['addState', 'RoomBoot', 'roomBoot', true]); //must be the last one
};