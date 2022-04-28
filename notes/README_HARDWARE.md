<div align=center>
<h1> :skull: VETCON BADGE :skull: <br/>
:stopwatch: :athletic_shoe: Hardware Overview </h1>
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
  - [:computer: Hardware Components](#computer-hardware-components)
    - [:one: Images](#one-images)
      - [:gear: PCB](#gear-pcb)
      - [:gear: Hardware Schematic](#gear-hardware-schematic)
      - [:gear: PCB Schematic](#gear-pcb-schematic)
    - [:two: Bill of Materials](#two-bill-of-materials)
      - [:gear: Purchasing Our Custom PCB](#gear-purchasing-our-custom-pcb)
      - [:gear: Options for Printing Our Custom Case](#gear-options-for-printing-our-custom-case)
    - [:three: Build Instructions](#three-build-instructions)
      - [:gear: Required Tools](#gear-required-tools)
      - [:gear: PCB Soldering Cheat Sheet](#gear-pcb-soldering-cheat-sheet)
      - [:gear: Soldering pins onto the PCB](#gear-soldering-pins-onto-the-pcb)
      - [:gear: Soldering the HC-05](#gear-soldering-the-hc-05)
      - [:gear: Soldering the 16x2 Screen](#gear-soldering-the-16x2-screen)
      - [:gear: Soldering the LEDs and Resistors](#gear-soldering-the-leds-and-resistors)
      - [:gear: Connecting to a Flashed MSP](#gear-connecting-to-a-flashed-msp)
    - [:four: MSP-EXP430FR2433](#four-msp-exp430fr2433)
      - [:gear: Image](#gear-image)
      - [:gear: Purpose](#gear-purpose)
    - [:five: Custom PCB](#five-custom-pcb)
      - [:gear: Image](#gear-image-1)
      - [:gear: Purpose](#gear-purpose-1)
    - [:six: HC-05](#six-hc-05)
      - [:gear: Image](#gear-image-2)
      - [:gear: Purpose](#gear-purpose-2)
    - [:seven: 16x2 Alphanumeric Screen](#seven-16x2-alphanumeric-screen)
      - [:gear: Image](#gear-image-3)
      - [:gear: Purpose](#gear-purpose-3)
    - [:eight: Smaller Components](#eight-smaller-components)
      - [:gear: Image](#gear-image-4)
      - [:gear: Purpose](#gear-purpose-4)
  - [:memo: Some Notes](#memo-some-notes)

## :star: About this Guide
<h5> THIS GUIDE IS INTENDED TO BE A DETAILED OVERVIEW OF OUR PROJECT'S HARDWARE IMPLEMENTATION </h5>
<h5> PLEASE USE THE INCLUDED MANUALS AS A 'FULL' REFERENCE FOR DEPLOYMENTS, BUILDS, ETC.</h5>

## :computer: Hardware Components

### :one: Images 

#### :gear: PCB
![PCB](https://github.com/derekbarbosa/EC463/blob/main/etc/pcb_top.JPG)
![PCB](https://github.com/derekbarbosa/EC463/blob/main/etc/pcb_bottom.JPG)
#### :gear: Hardware Schematic
![Hardware Schematic](https://github.com/derekbarbosa/EC463/blob/main/etc/schematic.png)
#### :gear: PCB Schematic
![PCB Schematic](https://github.com/derekbarbosa/EC463/blob/main/etc/pcb_schematic.png)

### :two: Bill of Materials

| Part | Quantity | Total Cost | Link |
|------|:--------:|------------|------|
|Two Pin Rocker Switch|1|$9.99|[Amazon](https://www.amazon.com/Twidec-Pre-soldered-Wires%EF%BC%88Quality-Assurance-KCD1-2-101-X-H/dp/B07SPVPQPL/ref=sr_1_7?keywords=2+pin+toggle+switch&qid=1649362072&sr=8-7)
|18650 3000mAh Lithium Battery|1|$6.99|[18650 Battery Store](https://www.18650batterystore.com/collections/18650-batteries/products/epoch-30p-18650)
|18650 Battery Holster|1|$6.99|[Amazon](https://www.amazon.com/ACEIRMC-Battery-Plastic-Storage-Connect/dp/B0986K3GVN/ref=sr_1_3?crid=3R9G21G1HKID6&keywords=1+slot+18650+holder&qid=1649364172&sprefix=1+slot+18650+holde%2Caps%2C75&sr=8-3)
|TI MSP- EXP430FR2433|1|$11.99|[Digikey](https://www.digikey.com/en/products/detail/texas-instruments/MSP-EXP430FR2433/7931876)
|16x2 Alphanumeric LCD|1|$9.19|[Amazon](https://www.amazon.com/HiLetgo-Display-Backlight-Controller-Character/dp/B00HJ6AFW6/ref=sr_1_3?keywords=HD44780&qid=1649365855&sr=8-3)
|3 Pin, 2-way microswitches|3|$8.99|[Amazon](https://www.amazon.com/Tnuocke-Vertical-Position-Switches-SS12D00-G3/dp/B099MRCDG8/ref=pd_lpo_1?pd_rd_i=B099MRCDG8&th=1)
|4 Pin Push button|1|$6.49|[Amazon](https://www.amazon.com/QTEATAK-Momentary-Tactile-Button-Switch/dp/B07VSNN9S2/ref=sr_1_2?crid=2NFCRS53B4EYJ&keywords=4+pin+push+button&qid=1649364273&sprefix=4+pin+push+button%2Caps%2C72&sr=8-2)
|HC-05 BT Module|1|$15.99|[Amazon](https://www.amazon.com/AEDIKO-Bluetooth-Transceiver-Integrated-Communication/dp/B09M6ZVJVR/ref=sr_1_19?crid=PQKO386NVIOA&keywords=HC-05+Bluetooth&qid=1649364332&sprefix=hc-05+bluetooth%2Caps%2C65&sr=8-19)
|18650 Battery Charger [Optional]|1|$18.99|[Amazon](https://www.amazon.com/Intelligent-Snado-Universal-Rechargeable-Batteries/dp/B0721JP6FK/ref=sr_1_3?crid=1Y82S5BQEIY2S&keywords=18650+battery+charger&qid=1649362929&sprefix=18650+battery+charger%2Caps%2C85&sr=8-3)

#### :gear: Purchasing Our Custom PCB

#### :gear: Options for Printing Our Custom Case

### :three: Build Instructions

#### :gear: Required Tools
<h5>Soldering: Some soldering experience and tools are required, but this is also a relatively simple soldering job. Thus, this project is recommended even for users wishing to learn or practice their soldering skill.</h5>
<h5>3D printing: Although you are free to download the necessary files and print the case on your own, this is not absolutely necessary as you are able to order a custom order through online shops.</h5>
<h5>Other tools: Phillips screwdriver and smaller screws.</h5>
    
#### :gear: PCB Soldering Cheat Sheet
<h5>This PCB is a prototype board, and is slightly different from the final product, but all soldering points are in the same place.</h5>
    
<h5>PCB Top</h5>
    
![Top](https://github.com/derekbarbosa/EC463/blob/main/etc/pcb_top.png)
<h5>PCB Bottom</h5>
    
![Bottom](https://github.com/derekbarbosa/EC463/blob/main/etc/pcb_bottom.png)
#### :gear: Soldering pins onto the PCB
#### :gear: Soldering the HC-05
#### :gear: Soldering the 16x2 Screen
#### :gear: Soldering the LEDs and Resistors
#### :gear: Connecting to a Flashed MSP

### :four: MSP-EXP430FR2433

#### :gear: Image
![MSP](https://github.com/derekbarbosa/EC463/blob/main/etc/msp.JPG)
#### :gear: Purpose
<h5>The MSP microcontroller is the component that runs all of our custom software, and manages all components on the device. The entire hardware design and software library are designed around this microcontroller.</h5>

### :five: Custom PCB

#### :gear: Image
![PCB Image](https://github.com/derekbarbosa/EC463/blob/main/etc/pcb_top.JPG)
#### :gear: Purpose
<h5>Our custom PCB is what allows the building process to be relatively simple, as it simplifies soldering each component to the MSP microcontroller. All components should be soldered to the PCB, which then is simply inserted into the socket risers on the MSP.</h5>

### :six: HC-05

#### :gear: Image
![HC-05](https://github.com/derekbarbosa/EC463/blob/main/etc/hc-05.JPG)
#### :gear: Purpose
<h5>The HC-05 is the component that allows our device to wirelessly connect to similar devices using Bluetooth, and is small enough to fit between the custom PCB and the MSP microcontroller.</h5>

### :seven: 16x2 Alphanumeric Screen

#### :gear: Image
#### :gear: Purpose
<h5>The alphanumeric screen is an important part of our device, as it allows each user to customise their badge and view their custom name on their device.</h5>

### :eight: Smaller Components

#### :gear: Image
#### :gear: Purpose

## :memo: Some Notes
If you'd like to continue this project, you might want to [fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) OR [duplicate](https://docs.github.com/en/repositories/creating-and-managing-repositories/duplicating-a-repository) this repository rather than attempting to push your own commits/do a pull request. This way, you get to have as much creative freedom with the code as you desire (obviously respecting the GNU GPL v3 license).

We intend to keep this repo as-is in a "finished" state. 

If you do have any questions, or make any cool developments/improvements that you would like to let us know about! Feel free to shoot us an email with the header: [GH EC463] + your name - {subject}

Happy hunting :)
