NAME = ircserv
SRC =	test.cpp \
		\
		src/obj/Cmd.cpp \
		src/obj/Client.cpp \
		src/obj/Channel.cpp \
		#$(wildcard src/*.cpp) \
		\
		#$(wildcard src/obj/*.cpp) \

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

re: fclean all

.PHONY: all clean fclean re
