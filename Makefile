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
SRCS = src/pipex.c src/utils.c src/ft_exec_split.c
SRCS_BONUS = bonus/pipex_bonus.c bonus/utils_bonus.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
LIBFT = ./libft/libft.a

all: $(NAME) libft 

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME)
	@cc $(OBJS) $(LIBFT) -o $(NAME)

.c.o:
	@cc $(FLAGS) -c $< -o $@

$(LIBFT):
	@make --silent -C ./libft
	@echo "$(PURPLE)██████╗ ██╗██████╗ ███████╗██╗  ██╗"
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝ "
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"
	@echo
	@echo "$(GREEN) Successfully compiled pipex.$(RESET)"
	@echo
	@echo

bonus: $(LIBFT) $(OBJS_BONUS)
	@cp $(LIBFT) $(NAME)
	@cc $(OBJS_BONUS) $(LIBFT) -o $(NAME)

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
	@rm -rf ./bonus/*.o
	@make --silent -C ./libft clean
	@clear
	@echo
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓"
	@echo "┃ ┃ ┣ ┣┫┃┃┣ ┃┃"
	@echo "┗┛┗┛┗┛┛┗┛┗┗┛┻┛"
	@echo

re: fclean all

.PHONY: libft pipex
