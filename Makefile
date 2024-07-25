RED    = $(shell printf "\33[31m")
GREEN  = $(shell printf "\33[32m")
WHITE  = $(shell printf "\33[37m")
YELLOW = $(shell printf "\33[33m")
RESET  = $(shell printf "\33[0m")
BLUE = $(shell printf "\33[34m")
PURPLE = $(shell printf "\33[35m")
TITLE = $(shell printf "\33[32;40m")

NAME = pipex
FLAGS = -Wall -Wextra -Werror -g
SRCS = pipex.c 
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

all: $(NAME) libft 

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME)
	@cc $(OBJS) $(LIBFT) -o $(NAME)

.c.o:
	@cc $(FLAGS) -c $< -o $@

$(LIBFT):
	@make --silent -C ./libft
	@echo "$(PURPLE)   __ _               _     _    __ "
	@echo "  / _| |_    _ __ _ _(_)_ _| |_ / _|"
	@echo " |  _|  _|  | '_ \ '_| | ' \  _|  _|"
	@echo " |_|  \\__|__| .__/_| |_|_||_\\__|_|  "
	@echo "        |___|_|                     "
	@echo
	@echo
	@echo "$(GREEN) Successfully compiled pipex.$(RESET)"
	@echo
	@echo

bonus: $(NAME)

fclean: clean
	@rm -f $(NAME)
	@make --silent -C ./libft fclean
	@clear
	@echo
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓"
	@echo "┃ ┃ ┣ ┣┫┃┃┣ ┃┃"
	@echo "┗┛┗┛┗┛┛┗┛┗┗┛┻┛"
	@echo

clean:
	@rm -rf *.o
	@rm -rf ./srcs/*.o
	@make --silent -C ./libft clean
	@clear
	@echo
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓"
	@echo "┃ ┃ ┣ ┣┫┃┃┣ ┃┃"
	@echo "┗┛┗┛┗┛┛┗┛┗┗┛┻┛"
	@echo

re: fclean all

.PHONY: libft
