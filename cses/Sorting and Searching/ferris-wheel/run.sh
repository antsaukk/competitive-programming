#!/bin/bash

if [ -d "bin/" ]
then
	rm -rf bin/
fi
mkdir bin
${CXX:-g++} -O3 -Werror -Wall --pedantic -fsanitize=address -fsanitize=undefined -std=c++17 -march=native -fopenmp -o ./bin/ferris-wheel ferris-wheel.cpp && ./bin/ferris-wheel
