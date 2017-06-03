
var arkanoidInit = function (game) {
    console.log("Initialize arkanoidInit");
    var NumberOfFilesToLoad = 3;
    var firstState = 'ArkanoidBoot';

    loadFile("arkanoid/arkanoidBoot.js", function () { afterLoading('ArkanoidBoot', 'arkanoidBoot'); });
    loadFile("arkanoid/arkanoidLoad.js", function () { afterLoading('ArkanoidLoad', 'arkanoidLoad'); });
    loadFile("arkanoid/arkanoid.js", function () { afterLoading('Arkanoid', 'arkanoid'); });

    function afterLoading(stateName, functionName) {
        addState(stateName, functionName);
        NumberOfFilesToLoad--;
        if (NumberOfFilesToLoad === 0) {
            console.log("Start state: " + firstState);
            this.game.state.start(firstState);
        }
    }
}