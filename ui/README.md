# ENGG1340-COMP2113-gp16
**This is Group 16 of the Course ENGG1340 && COMP2113 (2023-24, 2nd semester)**

## Contributors
Li Wenbo UID: 3036128638 <br>
Sun Xueli UID: 3036127218<br>
Tu Jingtian UID: 3036128121 <br>
Wang Zixuan UID: 3036128705 <br>
Zhen Qi UID: 3036127402

## Description
"Pyramid" is originated from the Pyramid game in "Microsoft solitaire & casual game". The goal of the Pyramid is to eliminate the deck by choosing any two cards that add up to 9, or one card that equals 9. There are two decks, which is distributed up and down respectively. The upper deck is in the shape of pyramid, and only the card at the bottom of the pyramid can be chosen. The deck below can be filped and the filped-up card in this deck can also be chosen, which make the operation of elimination more flexible and interesting.

## Game Rules
1. The green cards are comprised of the cards at the bottom of the upper deck and the deck below which can be fliped up. The white cards are the rest of the cards.
2. During the game period, player can only choose the green card to operate the elimination.
3. A successful elimination can be achieved by choosing any two cards that add up to 9, or one card that equals 9. The choice is made by inputting the suit and number of the card. For example, if the player want to choose "6 of spades", he/she needs to input "S6". If the player want to choose two cards, he/she needs to input one by one, like "S1" (press enter) "S6" (press enter).
4. When there's no proper choice in current situation, player can use the "flip" function. The deck at the bottom would be fliped up once for each 'f'. With the filped up card, elimination may be easier. When the deck is filped to the end, the player can input 'f' again and the deck would be reset without the cards that have been eliminated. But remember, the deck can be reset maximum 2 times.

## Key Features
1.Simple game rules that make every players to get started. <br>
2.Unique interface. <br>
3.Randomly generated deck, brings players excited game experience. <br>
4.Save system enables player to start from the step he/she played last time. <br>

## Requirements Implementation
### 1.Generation of random decks
* The deck for every new games is generated randomly by using function rand().

### 2.Data structure for storing the status of cards
* Each card's status, suit and number are stored in a structure so that each card can be identified flexibly.
* All the cards are coordinated in arrays so that the deck can be kept safely during the game period.

### 3.Dynamic memory management
* for in-game operation, we use a STL vector(vector<string>) to store command lines that the user input.
* The vector will be cleaned after the game finished.

### 4.File input/output
* File input and output are implemented in the game status storage.
* Game status is loaded by "" and saved by "" under the folder "".
  When the player exits the game, they can choose whether to save the game data or not.
  When the player logs in the game again, they can choose whether to start a new game or start from
  the old game.

### 5.Program codes in multiple files
* Program codes are split into different files according to their functions and sorted under different folders.

### 6.Proper indentation and naming style
* We follow the requirements of proper indentation and naming style carefully.

### 7.In-code documentation
* For each functions, we comment on "what it does", "what the inputs are", "what the outputs are".

## Libraries
* C++ libraries being used include: <br>
iostream, ctime, fstream, sstream, filesystem, cstdlib, vector, string, algorithm, cmath

* Additional library being used include: <br>
ncurses-6.4 <br>
<sub>The library ncurses is used to write user interfaces in a terminal-independent manner. It enables interactive console-based applications with text formatting and keyboard input features. <br>
Ncurses is mainly used to read keyboard input and output text to the terminal screen. For instance, the getch() function is used to read user input from the keyboard. It waits for the user to press a key and returns the corresponding ASCII code of the key pressed. It helps implement single-key actions, including moving the Pacman in the maze map and selecting an option from the game menu. <br>
Ncurses also optimizes screen changes to reduce the latency experienced when using remote shells. The refresh() function is used to update the physical screen with the content of the virtual screen in the welcomeLoop(). Any changes to the virtual screen will not be immediately visible on the physical screen until refresh() is called. After the user has provided input and the program has updated the virtual screen accordingly, refresh() is called to display the updated content on the physical screen.</sub>

## Instructions
Start the game with these commands: 
```
make .....
make clean
make
./bin/main
```

## Introduction Video

## Hope you enjoy our game!!!
