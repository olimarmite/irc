# Project #
NAME	=	ircserv

# Compiler #
CXX			=	c++
CXX_FLAGS	=	-Wall -Wextra -Werror -std=c++98
RM			=	rm -rf

# Objects #
OBJ_DIR		=	.objFiles

# Files #
SRC_DIR		=	srcs
INC_DIR		=	includes

SRC_FILES	:=	./srcs/irc/state_management/ChannelManager.cpp \
				./srcs/irc/state_management/UserManager.cpp \
				./srcs/irc/message_processing/CommandHandler.cpp \
				./srcs/utils/utils.cpp \
				./srcs/signals/signals.cpp \
				./srcs/commands/command_join.cpp \
				./srcs/commands/command_user.cpp \
				./srcs/commands/command_topic.cpp \
				./srcs/commands/commands_utils/join_utils.cpp \
				./srcs/commands/commands_utils/nick_utils.cpp \
				./srcs/commands/commands_utils/invite_utils.cpp \
				./srcs/commands/commands_utils/sendmsg_utils.cpp \
				./srcs/commands/commands_utils/mode_utils.cpp \
				./srcs/commands/commands_utils/kick_utils.cpp \
				./srcs/commands/commands_utils/topic_utils.cpp \
				./srcs/commands/command_nick.cpp \
				./srcs/commands/command_pass.cpp \
				./srcs/commands/command_invite.cpp \
				./srcs/commands/command_mode.cpp \
				./srcs/commands/command_kick.cpp \
				./srcs/commands/command_sendmsg.cpp \
				./srcs/networking/Client.cpp \
				./srcs/networking/Server.cpp \
				./srcs/networking/ClientManager.cpp \
				./srcs/models/User.cpp \
				./srcs/main.cpp

OBJ_FILES	:=	$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

INC_FILES	:=	./includes/signals.hpp \
.				./includes/Macros.hpp \
.				./includes/CommandHandler.hpp \
.				./includes/ChannelManager.hpp \
.				./includes/User.hpp \
.				./includes/ClientManager.hpp \
.				./includes/Client.hpp \
.				./includes/IrcReplies.hpp \
.				./includes/Server.hpp \
.				./includes/utils.hpp \
.				./includes/ServerSettings.hpp \
.				./includes/UserManager.hpp

#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
RESET		=	\e[0m

# Progress bar variables
TOTAL		:=	$(words $(SRC_FILES))
COUNT		:=	0

.PHONY: all clean fclean re

# Rules #
all: $(NAME)

$(NAME): $(OBJ_FILES) $(INC_FILES)
	@$(CXX) $(OBJ_FILES) -I $(INC_DIR) -o $(NAME)
	@printf "\n\n$(GREEN)	- Executable ready.\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_FILES)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(YELLOW)	- Object files removed.\n$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)	- Executable removed.\n\n$(RESET)"

re: fclean all
