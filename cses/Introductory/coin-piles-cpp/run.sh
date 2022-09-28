#!/bin/bash

if [ -d "bin/" ]
then
	rm -rf bin/
fi
mkdir bin
${CXX:-g++} -O3 -Werror -Wall --pedantic -fsanitize=address -fsanitize=undefined -std=c++17 -march=native -fopenmp -o ./bin/coin-piles coin-piles.cpp && ./bin/coin-piles
