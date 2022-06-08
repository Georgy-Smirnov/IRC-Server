#!/bin/bash

args=("$@")
clang++ -g server.cpp main.cpp handle_command.cpp -fsanitize=address && ./a.out ${args[0]} ${args[1]}