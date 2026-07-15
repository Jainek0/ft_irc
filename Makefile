NAME := ircserv

SRC := main.cpp \
		src/class/Channel.cpp \
		src/class/Client.cpp \
		src/class/Cmd.cpp \
		src/class/Command.cpp \
		src/class/Server.cpp \
		src/tools/logScript.cpp \
		src/tools/split.cpp \
		src/tools/toSize_t.cpp

CC := c++

CFLAGS := -Werror -Wextra -Wall -g --std=c++98

# OBJDIR = obj
OBJ = $(SRC:.cpp=.o)
# OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

all : $(OBJ) $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean :
	@rm -rf $(OBJDIR) 

fclean : clean 
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus