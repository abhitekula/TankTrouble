cmake_minimum_required(VERSION 3.10)
project(final_project_abhitekula)

set(CMAKE_CXX_STANDARD 11)

include_directories(TankTrouble/src)

add_executable(final_project_abhitekula
        TankTrouble/bin/data/tank.dat
        TankTrouble/bin/libs/libfmodex.so
        TankTrouble/bin/TankTrouble
        TankTrouble/obj/linux64/Release/src/main.d
        TankTrouble/obj/linux64/Release/src/main.o
        TankTrouble/obj/linux64/Release/src/ofApp.d
        TankTrouble/obj/linux64/Release/src/ofApp.o
        TankTrouble/src/main.cpp
        TankTrouble/src/ofApp.cpp
        TankTrouble/src/ofApp.h
        TankTrouble/addons.make
        TankTrouble/config.make
        TankTrouble/Makefile
        TankTrouble/TankTrouble.qbs
        PROPOSAL.md
        README.md)
