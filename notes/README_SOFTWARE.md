<div align=center>
<h1> :skull: VETCON BADGE :skull: <br/>
:stopwatch: :athletic_shoe: Quick Start Guide </h1>
<h3> For the full manuals, please view the following: </h3>
<h4>
<h4>
    <a href="notes/README_Engineering.md">Engineering Guide</a>
  <span> · </span>
    <a href="notes/README_HARDWARE.md">Hardware Guide</a>
</h4>

</div>


# :notebook_with_decorative_cover: Table of Contents
- [:notebook_with_decorative_cover: Table of Contents](#notebook_with_decorative_cover-table-of-contents)
  - [:star: About this Guide](#star-about-this-guide)
  - [:computer: Software Components](#computer-software-components)
    - [:one: Microcontroller Code](#one-microcontroller-code)
      - [:gear: Compilation](#gear-compilation)
      - [:gear: Function](#gear-function)
      - [:gear: Bluetooth](#gear-bluetooth)
    - [:two: Game 1](#two-game-1)
      - [:gear: Deployment](#gear-deployment)
      - [:gear: Interaction](#gear-interaction)
    - [:three: Game 2](#three-game-2)
      - [:gear: Deployment](#gear-deployment-1)
      - [:gear: Interaction](#gear-interaction-1)
    - [:four: Game 3](#four-game-3)
      - [:gear: Compilation](#gear-compilation-1)
      - [:gear: Interaction](#gear-interaction-2)
  - [:memo: Some Notes](#memo-some-notes)

## :star: About this Guide
<h5> THIS GUIDE IS A DETAILED OVERVIEW OF OUR PROJECT'S SOFTWARE IMPLEMENTATION AND DEPLOYMENT </h5>

## :computer: Software Components

### :one: Microcontroller Code 
<h5> <b>MSP430-FR2433 Chip Code</b> </h5>

#### :gear: Compilation
<h5> 
Compilation of the original source code (<code>EC463/src/VETCON/src/main.cpp</code>) is done through PlatformIO, a platform that interacts with the Wiring Framework to allow developers to use the Arduino format standard for any number of microcontrollers. Following the execution of a PlatformIO Build, a <code>firmware.elf</code> file is generated in the <code>.pio/$(PLATFORM_NAME)/ </code> folder of the project directory, which contains all of the linked firmware to be flashed to the board. This <code>firmware.elf</code> file is to be distributed to end users of the board, attending DEFCON, as a way to reflash their board in the situation where the board memory becomes corrupted. To reflash the board with the <code>firmware.elf</code>, one can use UniFlash, locate the board as a serial interface and then place in the location of the <code>firmware.elf</code> file, wherever the user has determined to store it.
</h5>

#### :gear: Function
<h5>
The MCU (Micro Controller Unit) code controls all of the on-board hardware, including the LEDs, buttons, LCD Screen, and the Bluetooth module (discussed in the following section in detail), as well as provides the user interaction methods by way of serial communication channels. The board can be interfaced with by way of buttons, but not in any useful way without a serial channel being opened up between a host and the board. Be sure to use a serial communication program that has implicit line endings, as otherwise formatting will be off. Once a user does plug in the board and open up a serial connection, they will need to be sure to kill the UniFlash process, as it takes up the board communication channel, and  do a soft reset of the board to make sure it sends out the "WELCOME TO VETCON" message (only on the first run), as well as the main menu. The main menu contains all of the options for user interaction: 

- <code>1. Set Name Tag</code>
- <code>2. Display Name Tag</code>
- <code>3. Game Link</code>
- <code>4. Game Link 2</code>
- <code>8. Start Bluetooth</code>
- <code>0. Reset Badge</code>

The list of possible inputs can expand over time, though, with the final menu being displayed as:

- <code>1. Set Name Tag</code>
- <code>2. Display Name Tag</code>
- <code>3. Game Link</code>
- <code>4. Game Link 2</code>
- <code>5. Secret Token</code>
- <code>6. Secret Token 2</code>
- <code>7. Secret Token 3</code>
- <code>8. Start Bluetooth</code>
- <code>9. LED CNTRL Menu</code>
- <code>0. Reset Badge</code>

These new options are revealed to the user through input of the secret codes, acquired through completion of the online games (discussed later in full). These codes are obfuscated when presented to the user, but here they are  translated, the exact encryption and decryption method for each code will be discussed in their corresponding game. The plaintext secret codes are as follows:

- <code>Game 1: "pizzatimetanthony"</code> 
  - <code>Unlocks: "6. Secret Token 2"</code> 
- <code>Game 2: "semperdisco"</code> 
  - <code>Unlocks: "7. Secret Token 3"</code> 
- <code>Game 3: "ilovevetcon"</code>

The process to begin inputting these secret codes is for the user to input: <code>9</code> to the initial menu. As the user inputs these secret codes into the device, external LEDs are lit in accordance with each unlocked secret, these are more aptly described in <code>README_HARDWARE.md</code>. Once all of the secrets have been unlocked, option <code>9. LED CNTRL Menu</code> is unlocked, allowing the user to choose the LED states to save power if they decide that is necessary. To control the LEDs, the user enters option <code>9. LED CNTRL Menu</code>, where they will be taken to the LED control menu, where they are presented with the following input options:

-   <code>1: Turn LEDs OFF</code>
-   <code>2: LED 'WAVE'</code>
-   <code>3: LED 'BLINK'</code>
-   <code>4: LED 'ALTERNATE'</code>
-   <code>5: Back 2 Main Menu</code>
</h5>

#### :gear: Bluetooth
<h5>
*JOHN KIRCHER SPOT*
</h5>

### :two: Game 1
<h5> Dino Run </h5>

#### :gear: Deployment
#### :gear: Interaction
<h5>

</h5>

### :three: Game 2
<h5> Coin Flip </h5>

#### :gear: Deployment
#### :gear: Interaction
### :four: Game 3
#### :gear: Compilation
#### :gear: Interaction

## :memo: Some Notes
If you'd like to continue this project, you might want to [fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) OR [duplicate](https://docs.github.com/en/repositories/creating-and-managing-repositories/duplicating-a-repository) this repository rather than attempting to push your own commits/do a pull request. This way, you get to have as much creative freedom with the code as you desire (obviously respecting the GNU GPL v3 license).

We intend to keep this repo as-is in a "finished" state. 

If you do have any questions, or make any cool developments/improvements that you would like to let us know about! Feel free to shoot us an email with the header: [GH EC463] + your name - {subject}

Happy hunting :)