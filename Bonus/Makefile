# Project #
NAME	=	ircbot

# Compiler #
CXX			=	c++
CXX_FLAGS	=	-Wall -Wextra -Werror -std=c++98
RM			=	rm -rf

# Objects #
OBJ_DIR		=	.objFiles

# Files #
SRC_DIR		=	srcs
INC_DIR		=	includes

SRC_FILES	:=	./srcs/main.cpp \
				./srcs/irc_bot.cpp \

OBJ_FILES	:=	$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

INC_FILES	:=	./includes/irc_bot.hpp \

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
