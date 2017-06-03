
var arkanoidBoot = function (game) {
    console.log("Initialize arkanoidBoot");
};

arkanoidBoot.prototype = {
    preload: function () {
        console.log("Enter arkanoidBoot");
    },
    create: function () {
        game.scale.setGameSize(480, 320);
        game.scale.scaleMode = Phaser.ScaleManager.SHOW_ALL;
        game.scale.pageAlignHorizontally = true;
        game.scale.pageAlignVertically = true;
        game.stage.backgroundColor = '#eee';
        game.scale.refresh();

        game.physics.startSystem(Phaser.Physics.ARCADE);
        game.physics.arcade.checkCollision.down = false;

        game.state.start("ArkanoidLoad");
    },
    shutdown: function () {
        console.log("Leave arkanoidBoot");
    }
}