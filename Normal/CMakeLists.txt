cmake_minimum_required(VERSION 3.28)
project(XO_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(XO_game
        BoardGame_Classes.h
        main.cpp
        PyramidX_O.h
        WordX_O.h
        WordX_O.h
        FiveX_O.h
        InverseX_O.h
        FourX_O.h
        3x3X_O.h
        FourInARow.h
        NumericalX_O.h
        SUSX_O.h
        ULTIMATE.h
        ULTIMATE.h
)
