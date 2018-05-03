# CS 126 Final Project Tank Trouble

## Description

Tank Trouble is a two player game where each person controls a tank. The goal is to kill the other person by navigating through the maze and shooting at them. Be careful to not shoot randomly because you can get hit by your own bullet. Along the way be sure to pick up powerups for an edge over your opponents. The only way to get more ammo after running out is through powerups. Game On!!!

## Prerequisites

* Openframeworks installed

## How to compile yourself

1. Download ofBox2d and add it to the addons folder in openframeworks.
https://github.com/vanderlin/ofxBox2d/tree/stable

2. Clone this repo and run the openframeworks project generator on the TankTrouble folder to update the project

3. Navigate to the TankTrouble folder and type in make in the command line.

4. Once it is done compiling run 'make RunRelease' in the current directory or navigate to the bin/ directory and run the TankTrouble executable.

## If you just want to start playing run the precompiled binary (Tested on linux)

1. Download the zip of the repository and unzip it.

2. Navigate to the TankTrouble/bin/ folder and run the TankTrouble executable.

## Instructions

#### How to move around:

* Player 1 - WASD to move around
* Player 2 - Arrow keys to move around

#### How to shoot

* Player 1 - 'E' to shoot
* Player 2 - '/' to shoot

#### Pausing

* Press P to toggle pause

#### After Round Ends

* Press R to start the next round

## Powerups

* Yellow - Max Ammo.
* Orange - Increased tank speed and bullet speed.
* Green - Max Health.
* Purple - Increased bullet speed.