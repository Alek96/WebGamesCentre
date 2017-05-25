
var arkanoid = function (game) {
    console.log("Initialize arkanoid");
};

arkanoid.prototype = {
    init: function () {
        this.__proto__.score = 0;
        this.__proto__.lives = 1;
        this.__proto__.playing = false; 

        this.__proto__.brickInfo = {
            width: 50,
            height: 20,
            count: {
                row: 7,
                col: 3
            },
            offset: {
                top: 50,
                left: 60
            },
            padding: 10
        }
        this.bricks = game.add.group();
        this.__proto__.parent = this;
    },
    preload: function () {
        console.log("Enter arkanoid");
    },
    create: function () {
        this.ball = game.add.sprite(game.world.width * 0.5, game.world.height - 25, 'arkanoidBall');
        this.ball.animations.add('wobble', [0, 1, 0, 2, 0, 1, 0, 2, 0], 24);
        this.ball.anchor.set(0.5);
        game.physics.enable(this.ball, Phaser.Physics.ARCADE);
        this.ball.body.collideWorldBounds = true;
        this.ball.body.bounce.set(1);
        this.ball.checkWorldBounds = true;
        this.ball.events.onOutOfBounds.add(this.ballLeaveScreen, this);

        this.paddle = game.add.sprite(game.world.width * 0.5, game.world.height - 5, 'arkanoidPaddle');
        this.paddle.anchor.set(0.5, 1);
        game.physics.enable(this.paddle, Phaser.Physics.ARCADE);
        this.paddle.body.immovable = true;

        this.initBricks();

        var textStyle = { font: '18px Arial', fill: '#0095DD' };
        this.scoreText = game.add.text(5, 5, 'Points: 0', textStyle);

        this.livesText = game.add.text(game.world.width - 5, 5, 'Lives: ' + this.__proto__.lives, textStyle);
        this.livesText.anchor.set(1, 0);

        this.lifeLostText = game.add.text(game.world.width * 0.5, game.world.height * 0.5, 'Life lost, tap to continue', textStyle);
        this.lifeLostText.anchor.set(0.5);
        this.lifeLostText.visible = false;

        this.startButton = game.add.button(game.world.width * 0.5, game.world.height * 0.5, 'arkanoidButton', this.startGame, this, 1, 0, 2);
        this.startButton.anchor.set(0.5);

        this.backButton = TextButton(30, game.world.height - 10, "Back", this.openBack, this, { font: '20px Arial', fill: '#black' });
    },
    update: function () {
        game.physics.arcade.collide(this.ball, this.paddle, this.ballHitPaddle);
        game.physics.arcade.collide(this.ball, this.bricks, this.ballHitBrick);
        if (this.__proto__.playing) {
            this.paddle.x = game.input.x || game.world.width * 0.5;
        }
    },
    shutdown: function () {
        console.log("Leave arkanoid");
    },

    initBricks: function () {
        var brickInfo = this.__proto__.brickInfo;
        var newBrick;

        for (c = 0; c < brickInfo.count.col; c++) {
            for (r = 0; r < brickInfo.count.row; r++) {
                var brickX = (r * (brickInfo.width + brickInfo.padding)) + brickInfo.offset.left;
                var brickY = (c * (brickInfo.height + brickInfo.padding)) + brickInfo.offset.top;
                newBrick = game.add.sprite(brickX, brickY, 'arkanoidBrick');
                game.physics.enable(newBrick, Phaser.Physics.ARCADE);
                newBrick.body.immovable = true;
                newBrick.anchor.set(0.5);
                this.bricks.add(newBrick);
            }
        }
    },
    ballHitBrick: function (ball, brick) {
        var killTween = game.add.tween(brick.scale);
        killTween.to({ x: 0, y: 0 }, 200, Phaser.Easing.Linear.None);
        killTween.onComplete.addOnce(function () {
            brick.kill();
        }, this);
        killTween.start();
        
        var context = arkanoid.prototype.parent;

        context.__proto__.score += 10;
        context.scoreText.setText('Points: ' + context.__proto__.score);
        if (context.__proto__.score === context.__proto__.brickInfo.count.row * context.__proto__.brickInfo.count.col * 10) {
            alert('You won the game, congratulations!');
            game.state.restart(true, false);
        }
    },
    ballLeaveScreen: function () {
        this.__proto__.lives--;
        if (this.__proto__.lives) {
            this.livesText.setText('Lives: ' + this.__proto__.lives);
            this.lifeLostText.visible = true;
            this.ball.reset(game.world.width * 0.5, game.world.height - 25);
            this.paddle.reset(game.world.width * 0.5, game.world.height - 5);
            game.input.onDown.addOnce(function () {
                this.lifeLostText.visible = false;
                this.ball.body.velocity.set(150, -150);
            }, this);
        }
        else {
            alert('You lost, game over!');
            game.state.restart(true, false);
        }
    },
    ballHitPaddle: function (ball, paddle) {
        ball.animations.play('wobble');
        ball.body.velocity.x = -1 * 5 * (paddle.x - ball.x);
    },
    startGame: function () {
        this.startButton.destroy();
        this.ball.body.velocity.set(150, -150);
        this.__proto__.playing = true;
    },

    openBack: function () {
        game.state.start('RoomBoot');
    },
};