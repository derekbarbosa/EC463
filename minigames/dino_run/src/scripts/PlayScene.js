import Phaser from 'phaser';

class PlayScene extends Phaser.Scene {

  constructor() {
    super('PlayScene');
  }

  create() {  
    const { height, width } = this.game.config;
    this.isGameRunning = false;
    this.gameSpeed = 10;
    this.respawnTime = 0;
    this.score = 0;
    this.max_score = 1016;

    this.ground = this.add.tileSprite(0, height, 88, 26, 'ground').setOrigin(0, 1); 

    this.startTrigger = this.physics.add.sprite(0, 10)
      .setOrigin(0, 1)
      .setImmovable();

    this.dino = this.physics.add.sprite(0, height, 'dino-idle')
      .setCollideWorldBounds(true)
      .setGravityY(5000)
      .setOrigin(0, 1);

    this.obsticles = this.physics.add.group();

    this.gameOverScreen = this.add.container(width / 2, height / 2 - 50).setAlpha(0);
    this.gameOverText = this.add.image(0, 0, 'game-over');
    this.restart = this.add.image(0, 80, 'restart').setInteractive();
    this.gameOverScreen.add([this.gameOverText, this.restart]);

    this.scoreText = this.add
      .text(width, 0, '00000', {fill: '#535353', font: '900 35px Courier', resolution: 5})
      .setOrigin(1, 0);

    this.congratsScreen = this.add.container(width / 2, height / 2 - 50).setAlpha(0);
    this.congratsText = this.add.image(0, 0, 'congrats');
    this.congratsScreen.add([this.congratsText]);

    this.inputHandler();
    this.initAnimations();
    this.initStartTrigger();
    this.initColliders();
    this.scoreHandler();
  }

  update(time, delta) {
    if(!this.isGameRunning) { return; }
    this.ground.tilePositionX += this.gameSpeed;
    Phaser.Actions.IncX(this.obsticles.getChildren(), -this.gameSpeed);
    this.respawnTime += delta * this.gameSpeed * 0.08;

    if(this.respawnTime >= 1500) {
      this.placeObsticle();
      this.respawnTime = 0;
    }

    if(this.dino.body.deltaAbsY() > 0) {
      this.dino.anims.stop();
      this.dino.setTexture('dino', 0);
    }
    else {
      this.dino.body.height <= 58 ? 
        this.dino.play('dino-down-anim', true) : 
        this.dino.play('dino-run', true);
    }

    this.obsticles.getChildren().forEach(obsticle => {
      if(obsticle.getBounds().right < 0) {
        obsticle.destroy();
      }
    })

    if(this.score >= this.max_score) {
      this.isGameRunning = false;
      this.physics.pause();
      this.congratsScreen.setAlpha(1);
      this.anims.pauseAll();
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('pizzatime');
      console.log('Well look what we have here: ' + 'AYKLPDX[TDPXEX^XH');
      console.log('Looks like this could be a hint (x)OR a detriment.')
      console.log('Anyways, have fun :)');
    }
  }

  inputHandler() {
    this.input.keyboard.on('keyup_SPACE', () => {
      if (!this.dino.body.onFloor()) { return; }
      this.dino.body.height = 92;
      this.dino.body.offset.y = 0;
      this.dino.setVelocityY(-1600);
    })

    this.input.keyboard.on('keydown_DOWN', () => {
      if(!this.dino.body.onFloor()) { return; }
      this.dino.body.height = 58;
      this.dino.body.offset.y = 34;
    })

    this.input.keyboard.on('keyup_DOWN', () => {
      if(!this.dino.body.onFloor()) { return; }
      this.dino.body.height = 92;
      this.dino.body.offset.y = 0;
    })

    this.restart.on('pointerdown', () => {
      this.dino.setVelocityY(0);
      this.dino.body.height = 92;
      this.dino.body.offset.y = 0;
      this.physics.resume();
      this.obsticles.clear(true, true);
      this.isGameRunning = true;
      this.gameOverScreen.setAlpha(0);
      this.anims.resumeAll();
    })
  }

  initAnimations() {
    this.anims.create({
      key: 'dino-run',
      frames: this.anims.generateFrameNumbers('dino', {start: 2, end: 3}),
      frameRate: 10,
      repeat: -1
    })

    this.anims.create({
      key: 'dino-down-anim',
      frames: this.anims.generateFrameNumbers('dino-down', {start: 0, end: 1}),
      frameRate: 10,
      repeat: -1
    })

    this.anims.create({
      key: 'enemy-dino-fly',
      frames: this.anims.generateFrameNumbers('enemy-bird', {start: 0, end: 1}),
      frameRate: 10,
      repeat: -1
    })
  }

  initStartTrigger() {
    const { width, height } = this.game.config;
    this.physics.add.overlap(this.startTrigger, this.dino, () => {
      if( this.startTrigger.y === 10) {
        this.startTrigger.body.reset(0, height);
        return
      }

      this.startTrigger.disableBody(true, true);
      const startEvent = this.time.addEvent({
        delay: 1000/60,
        loop: true,
        callbackScope: this,
        callback: () => {
          this.dino.setVelocityX(100);
          this.dino.play('dino-run', 1);
          if(this.ground.width < width) {
            this.ground.width += 17 * 2;
          }

          if(this.ground.width >= width) {
            this.ground.width = width;
            this.isGameRunning = true;
            this.dino.setVelocity(0);
            startEvent.remove();
          }
        }
      })
    }, null, this);
  }

  placeObsticle() {
    const { width, height } = this.game.config;
    const obsticleNum = Math.floor(Math.random() * 7) + 1;
    const distance = Phaser.Math.Between(600, 900);
    
    let obsticle;
    if(obsticleNum > 6) {
      const enemyHeight = [22, 50];
      obsticle = this.obsticles.create(width + distance, height - enemyHeight[Math.floor(Math.random() * 2)], 'enemy-bird')
      obsticle.play('enemy-dino-fly', 1);
      obsticle.body.height = obsticle.body.height / 1.5;
    }
    else {
      obsticle = this.obsticles.create(width + distance, height, `obsticle-${obsticleNum}`)
      obsticle.body.offset.y = 10;
    }

    obsticle
      .setOrigin(0, 1)
      .setImmovable();
  }

  initColliders() {
    this.physics.add.collider(this.dino, this.obsticles, () => {
      this.physics.pause();
      this.isGameRunning = false;
      this.anims.pauseAll();
      this.dino.setTexture('dino-hurt');
      this.respawnTime = 0;
      this.gameSpeed = 10;

      this.gameOverScreen.setAlpha(1);

      this.score = 0;
    }, null, this)
  }

  scoreHandler() {
    this.time.addEvent({
      delay: 100,
      loop: true,
      callbackScope: this,
      callback: () => {
        if(!this.isGameRunning) { return; }
        this.score+=2;
        this.gameSpeed += 0.035;
        const score = Array.from(String(this.score), Number);
        for(let i = 0; i < 5 - String(this.score).length; i++) {
          score.unshift(0);
        }
        this.scoreText.setText(score.join(''));
      }
    })
  }
}

export default PlayScene;
