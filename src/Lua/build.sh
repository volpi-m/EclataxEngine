#!/bin/bash

g++ --std=c++17 src/*.cpp main.cpp -W -Wall -Wextra -iquote src -llua -ldl && ./a.out
