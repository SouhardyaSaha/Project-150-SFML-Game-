#!/bin/bash
g++ -c main.cpp
g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
