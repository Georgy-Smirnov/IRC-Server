#!/bin/bash

args=("$@")
clang++ -g server.cpp main.cpp handle_command.cpp && ./a.out ${args[0]} ${args[1]}