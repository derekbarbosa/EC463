# Senior Design Session 1 Logbook.

Copyright Year 2021 Derek Deoliveira Barbosa dbarbosa@bu.edu
https://www.github.com/derekbarbosa
https://www.dbarbosa.net

## September
Entries here will be reserved specifically for the remainder of September.

### 9/20/2021
* Project Teams are assigned.
* Assigned to Team 32 -- VETCON BADGE
* Reviewed and began to interact with team members

### 9/21/2021
* Regrouped with team. Took team photos, decided to hold off on hitting the ground running until the following day

### 9/22/2021
* Started a Slack Workspace to manage group communication
	- Integrated BU Google Workspace Calendar into Slack Integrations
	- Started a Trello Board to manage project details, integrated to Slack
	- Created a Team Calendar to keep track of "who is in class" and facilitate the arrangement of meeting times.
	- Got in contact with client to arrange meeting time. Tentative for 9/24/2021 3PM Eastern.
	- Assigned the task of formulating questions for the client for further information on desired specifications to team members who would not be present during the inital cient meeting.

### 9/23/2021
* Finalized meeting details with our client. Confirmed for 9/24/2021 3pm eastern.
* Began drafting questions based on project requirements. Instructed group members to do the same.
* Set up a GH repo for our documentation. Linked to Slack Channel using webhooks to keep version control hygiene.

### 9/24/2021
* Met with clients! 
* attached notes for client meeting
* Ryan said he would take care of the inital PDRR writeup, will pause work for the weekend.

### 9/27/2021
* Brainstorming approach to IC/embedded system approach as described by client
* during review of the product specifications, clients emphasized battery life and weight
	* asked us to be somewhat conservative with the tradeoff
* started to look at TI-83/84 PCBs, determining best practices to create a low-power system with programmable memory.
* attaching notes to this upload :)

### 9/28/2021
* talk about rabbit hole research about calculators and low-power electronics
* Did a little more research on calculators and their "mini" operating system
	* this is following up on the design requirements from the client. They desired something that was "hackable" and easily "dumpable." They didn't need a "full" OS as we know today (Raspbian, etc) but would be fine with basic operating systems/firmware controller software.
	* Why so much research into calculators -- they are low power "embedded systems" that run off of AA batteries (less than 1100 mAh) for months at a time, with built-in save state and sleep cycles. Programmable Memory + ROM combination with fast (near instant) boot times.
	* Specifically looking into implementing KnightOS, a FOSS calculator OS that can run on TI-83/84s.
	* TI-83/84/84plus/84CE run on Zilog Z80, same processor in the old Sinclair Computers and other older computing systems. Easy to breadboard and fairly understandable datasheet compared to more modern microprocessors. Fairly straightforward ASM implementation as well if any need to get "manual" with the code.

* Much harder than just plugging in a Raspberry Pi Zero/Zero-W and calling it a day. But you get massive flexibility tradeoff + battery life
	* RPI consumes 1A with a few plugins/accessories running, would need 120WH battery (bigger than FAA/FCC limit) to power the device for 24 hours
	* RPI allows for easy compatiability with COTS components and rpi-approved "hats" out of GPIO plugins
	* benefit of working with linux kernel directly + debian-based OS tools.

* Met with Team -- reviewed the zoom call notes and discussed the approaches above. 
* Assigned John Kircher as the Team Leader for the first rotation. He will be working on the PDRR. I will contribute to the slide deck.

## October
Entries here will be reserved specifically for the month of October.

### 10/1/2021

* Researched ISA/Microprocessor compatability with KnightOS and Espilon OS (open source "calculator" operating systems that can be forked and edited for specific functionality.

* Began to look into parts ordering, accounting for 50 dollar budget.

* Created a slides template for the PDRR review


### 10/3/2021
* Preparing for PDRR initial presentation 10/7
* Not many new updates -- quick tag-up with team about next steps and what "we want to do" with our lead time
* Reviewed Presentation slides and script, made some edits to specifications
* Began working on PDRR written report

### 10/5/2021
* Attempted to find an easier middle ground between high-power (but flexible) SBC (single-board-computer) such a rasberry PI and manually soldering together an MCU and ROM.
* Encountered complete "embedded" development kits, closer to an SOC (think Arduino Uno's ATMEGA MCU / ESP32) but with an emphasis on ultra-low power consumption without entirely sacrificing QoL IDE tools
	* Board(s) of question: Texas Instruments "LaunchPad" development kits for the ultra-low power MSP430 MCU family -- https://www.ti.com/design-resources/embedded-development/hardware-kits-boards.html#launchpad
* Why this approach? 
	* As mentioned in the bullet above, Power Consumption is something our team needs to account for at all time.
	* The MSP430 famiy consumes 1.3 µA on average, and can still send enough power to "juice" a LFR display.
	* "mini" or "micro" MCU devkits allow us to have a consistent environment to prototype our code if we decide to just use an MSP430 and ROM soldered directly onto a board.
	* Enables flexibility with IDEs and built-in code snippets for code re-use
	* Can also leverage other family of MCUs, such as the ESP32 family.
	* Specifically, the FireBeetle https://www.dfrobot.com/product-1590.html -- has a low power consumption of 0.011 mA.
* Next steps?
	* Do some research of sample projects using these DevKits -- what are some issues that developers run into when debugging these boards
	* Look at some other DefCon badges that leveraged Arduino/arduino-like SOCs (especially their open-source git repos)
	* Review datasheets and peripheral compatability
	* Relay research back to Client -- inform them of approach
	* Compare SOC approach vs SBC vs Bare-Metal
	* Look into reverse-engineering SOC into bare-metal PCB
### 10/8/2021
* Regrouped with Team -- agreed to vote on specific approach next monday.
* Discussed at length the pros+cons of each architecture, we described our preferences and laid out our "greivances"
* Relayed that we might not hit power consumption requirements if we follow up with RPI approach.
* Decided as a team to "take off" until after Indigenous People's Day

### 10/12/2021
* Team has decided to go with DevKit approach. I will put orders in for MSP420s (low power) and Arduno Minis (that can leverage the low-power settings)
* Will also put in an order for a Digital Multimeter, maybe some breadboards too (so they can arrive in time).
* Started drafting some sketches describing how we would program the SOC memory using the built-in IDEs provided to us.
* John released the first draft of our PDRR -- Started to revise and edit some of the content for the final review prior to submission

### 10/15/2021
* Started to review datasheets for the MSP420/430 programming specifications
* installed the Eclipse-based IDE and verified debugging functionality (IDE specific to the TI LaunchPad board)
* Gathering materials and slide decks to present to our client again this saturday.
* Putting in orders for additional LEDs and Breadboards -- looking into drafting some starter designs to meet the creative aspect of the assignment.
* Began to look for example code to pull "inspiration" about starter code.

### 10/18/2021
* Discussed upcoming "plan of attack" with team. Realigned goals and applied pivots to tasks.
* Established a variety of roles for the project:
	- Software
	- Power Consumption 
	- Hardware/PCB design
	- Hacking Minigame
* The four roles align somewhat well with the 5 teammembers, as we have a good mix of skills. I volunteered myself for SW debugging
* Discussed how to set up our inital dev cycles upon arrival of our hardware (TIMSP430).
* Filled in the rest of team on how/why we should consider meeting up once or twice a week to do merges and progress meetings (to align with agile fashion)
* Presented MVP to VETCON Client, edited slides to reflect Shark Tank Presentation.

