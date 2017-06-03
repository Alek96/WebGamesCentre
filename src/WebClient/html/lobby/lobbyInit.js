roomInit();

function roomInit() {
    console.log("Initialize lobbyInit");
    var NumberOfFilesToLoad = 3;
    var firstState = 'LobbyBoot';

    loadFile("lobby/lobbyBoot.js", function () { afterLoading('LobbyBoot', 'lobbyBoot'); });
    loadFile("lobby/lobbyLoad.js", function () { afterLoading('LobbyLoad', 'lobbyLoad'); });
    loadFile("lobby/lobby.js", function () { afterLoading('Lobby', 'lobby'); });

    function afterLoading(stateName, functionName) {
        addState(stateName, functionName);
        NumberOfFilesToLoad--;
        if (NumberOfFilesToLoad === 0) {
            console.log("Start state: " + firstState);
            this.game.state.start(firstState);
        }
    }
}