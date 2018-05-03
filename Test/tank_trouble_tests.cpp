#include <iostream>

#define CATCH_CONFIG_MAIN

#include "catch.h"
#include "../TankTrouble/src/tank.h"
#include "../TankTrouble/src/maze.h

TEST_CASE("tankShootTest") {
    Tank tank;
    int num_ammo = tank.getAmmo();
    tank.shoot();
    REQUIRE(tank.getAmmo() == num_ammo -1);
}

TEST_CASE("mazeLoadTest") {
    Maze maze("maze1Edges.txt", "maze1StartingPositions.txt");

    REQUIRE(maze.getStartingPosition());
}
