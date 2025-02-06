# ColourSwitchGame

## Introduction:

This project is a replication of the popular mobile game "Color Switch" using `C++` and the `SFML` library and is built as a 2nd Semester project for the CS1004 Object Oriented Programming Course. The game uses and implements OOP concepts to build a user-friendly and challenging gaming environment.

## Features
1- Ball Jump Physics

2- Level-Based Gameplay

3- Color match detection

4- Ball-Obstacle Collision Detection

5- Scoring System

## Instructions to run the game:
1- Download the repository as a `zip` folder and extract all files.

2- Open the terminal inside the extracted directory

3- Replace the text inside `<>` with the paths specified and run the commands:

a- **For compilation**:  `g++ -c main-combined.cpp -I"<Replace with path of 'include' folder>";g++ main-combined.o -o main-combined -L"<Replace with path of 'lib' folder>" -lsfml-graphics -lsfml-window -lsfml-system`

b- **To run**: `./main-combined`
## Contributers:

1- @AbdulRahman9075 (Group Leader): Built the user interface, game structure and block-based obstacles.

2- @Sadiq-Amin: Built polygon-based obstacles.

3- @jagdesh666:  Implemented ball motion physics.

## Known Issues:
- Collision Detection Algorithm does not function properly.
