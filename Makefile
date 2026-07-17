NAME := ircserv

NAME_BONUS := spambot

SRCDIR = src
SRCDIR_BONUS = bonus
OBJDIR = obj
OBJDIR_BONUS = obj

SRC := main.cpp \
		class/Channel.cpp \
		class/Client.cpp \
		class/Cmd.cpp \
		class/Command.cpp \
		class/Server.cpp \
		tools/logScript.cpp \
		tools/split.cpp \
		tools/toSize_t.cpp

SRC_BONUS = src_bonus/main_bonus.cpp \
			src_bonus/Cmd.cpp \
			src_bonus/Spambot.cpp

CC := c++

CFLAGS := -Werror -Wextra -Wall -g --std=c++98

OBJ = $(SRC:.cpp=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))
OBJ_BONUS = $(SRC_BONUS:.cpp=.o)
OBJ_BONUS := $(addprefix $(OBJDIR_BONUS)/, $(OBJ_BONUS))

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all : $(OBJ) $(NAME) bonus

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $^

$(OBJDIR_BONUS)/%.o: $(SRCDIR_BONUS)/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $^

clean :
	@rm -rf $(OBJDIR) 

fclean : clean 
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -f irc.log

re : fclean $(NAME)

.PHONY : all clean fclean re bonus