#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "server.hpp"

#define WELCOME " :Welcome to the Internet Relay Network "
#define RPL_MOTDSTART "- Message of the day -\r\n"
#define RPL_MOTD1 " 372  : \r\n"
#define RPL_MOTD2 " 372  : HELLO, WORLD!!!\r\n"
#define RPL_MOTD3 " 372  :    ヽ༼ ಠ益ಠ ༽ﾉ\r\n"
#define RPL_MOTD4 " 372  : WELCOME TO IRC SERVER\r\n"
#define RPL_MOTD5 " 372  : ༼∵༽ ༼⍨༽ ༼⍢༽ ༼⍤༽\r\n"
#define RPL_MOTD6 " 372  :   ༼⍢༽ ༼⍨༽ ༼⍤༽ ༼∵༽\r\n"
#define RPL_ENDOFMOTD " 376  : End of /MOTD command\r\n"
#define RPL_YOUREOPER " 381 :You are now an IRC operator\r\n"
//ERRORS
#define ERR_NOSUCHNICK " :No such nick/channel\r\n"
#define ERR_NICKNAMEINUSE " :Nickname is already in use\r\n"
#define ERR_UNKNOWNCOMMAND " :Unknown command\r\n"
#define ERR_NOTREGISTERED " 451  :You have not registered\r\n"
#define ERR_NEEDMOREPARAMS " 461  OPER :Not enough parameters\r\n"
#define ERR_PASSWDMISMATCH " 464  :Password incorrect\r\n"
#define ERR_CHANOPRIVSNEEDED " :Permission Denied- You're not an IRC operator\r\n"

#endif