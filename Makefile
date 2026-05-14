NAME = ircserv
SRC =	test.cpp \
		\
		$(wildcard src/tools/*.cpp) \
		\
		$(wildcard src/class/*.cpp) \
		\
		$(wildcard src/*.cpp) \

OBJ = $(SRC:.cpp=.o)

CFLAGS = -Werror -Wextra -Wall -g --std=c++98


all:	$(NAME)

$(NAME): $(OBJ)
	c++ $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	c++ $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f irc.log

re: fclean all

.PHONY: all clean fclean re
