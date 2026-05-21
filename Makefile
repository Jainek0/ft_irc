NAME = ircserv

SRC =	main.cpp \
		src/class/Client.cpp\
		src/class/Command.cpp\
		src/class/Server.cpp\
# 		$(wildcard src/*.cpp) \
		$(wildcard src/class/*.cpp) \
		\
# 		$(wildcard src/tools/*.cpp) \
# 		$(wildcard src/tools/*.tpp) \
# 		\

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
