NAME = ./ircserv
SRCS = channel.cpp client.cpp handle_command.cpp main.cpp server.cpp
HEADER  = channel.hpp client.hpp handle_command.hpp server.hpp message.hpp
SRCS_BOT = botislav.cpp


all: $(NAME)

$(NAME) : $(SRCS) $(HEADER)
	c++ -fsanitize=address -g $(SRCS) -o ircserv

bot: $(SRCS_BOT)
	c++ $(SRCS_BOT) -o bot
