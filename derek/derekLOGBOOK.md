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

