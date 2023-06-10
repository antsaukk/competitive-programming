#!/bin/bash

if [ -d "bin/" ]
then
	rm -rf bin/
fi
mkdir bin
clang++ -O3 -Werror -Wall --pedantic  -std=c++17 -o ./bin/building_teams building_teams.cpp && ./bin/building_teams
