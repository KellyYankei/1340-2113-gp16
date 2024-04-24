# 1340-2113-gp16
**This is Group 16 of the Course ENGG1340 && COMP2113**

## Contributors
Li Wenbo UID: <br>
Sun xueli UID: <br>
Tu Jingtian UID: <br>
Wang Zixuan UID: <br>
Zhen Qi UID:

## Description

## Game Rules

## Key Features

## Requirements Implementation

## Libraries
* C++ libraries being used include: <br>
iostream, fstream, sstream, filesystem, cstdlib, vector, string,algorithm

* Additional library being used include: <br>
ncurses-6.4 <br>
<sub>The library ncurses is used to write user interfaces in a terminal-independent manner. It enables interactive console-based applications with text formatting and keyboard input features. <br>
Ncurses is mainly used to read keyboard input and output text to the terminal screen. For instance, the getch() function is used to read user input from the keyboard. It waits for the user to press a key and returns the corresponding ASCII code of the key pressed. It helps implement single-key actions, including moving the Pacman in the maze map and selecting an option from the game menu. <br>
Ncurses also optimizes screen changes to reduce the latency experienced when using remote shells. The refresh() function is used to update the physical screen with the content of the virtual screen in the welcomeLoop(). Any changes to the virtual screen will not be immediately visible on the physical screen until refresh() is called. After the user has provided input and the program has updated the virtual screen accordingly, refresh() is called to display the updated content on the physical screen.</sub>

## Instructions
Start the game with these commands:
```
make clean
make
./bin/main
```

## Introduction Video

## Hope you enjoy our game!!!
