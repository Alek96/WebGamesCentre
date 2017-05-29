
var roomInit = function () {
    console.log("Initialize roomInit");
    var NumberOfFilesToLoad = 3;
    var firstState = 'RoomBoot';

    loadFile("room/roomBoot.js", function () { afterLoading('RoomBoot', 'roomBoot'); });
    loadFile("room/roomLoad.js", function () { afterLoading('RoomLoad', 'roomLoad'); });
    loadFile("room/room.js", function () { afterLoading('Room', 'room'); });

    function afterLoading(stateName, functionName) {
        addState(stateName, functionName);
        NumberOfFilesToLoad--;
        if (NumberOfFilesToLoad === 0) {
            console.log("Start state: " + firstState);
            game.state.start(firstState);
        }
    }
};