#!/bin/bash

CLIENT="udp_client.c"
SERVER="udp_server.c"
gcc -o client $CLIENT
printf "\033[2K\r\e[32m Client create. \e[0m✅\n"
gcc -o server $SERVER
printf "\033[2K\r\e[32m Server create. \e[0m✅\n"