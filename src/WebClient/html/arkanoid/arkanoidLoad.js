
var arkanoidLoad = function (game) {
    console.log("Initialize arkanoidLoad");
};

arkanoidLoad.prototype = {
    preload: function () {
        console.log("Enter arkanoidLoad");

        game.load.image('arkanoidPaddle', 'arkanoid/img/paddle.png');
        game.load.image('arkanoidBrick', 'arkanoid/img/brick.png');
        game.load.spritesheet('arkanoidBall', 'arkanoid/img/wobble.png', 20, 20);
        game.load.spritesheet('arkanoidButton', 'arkanoid/img/button.png', 120, 40);
    },
    create: function () {
        game.state.start("Arkanoid");
    },
    shutdown: function () {
        console.log("Leave arkanoidLoad");
    }
}