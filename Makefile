RED    = $(shell printf "\33[31m")
GREEN  = $(shell printf "\33[32m")
WHITE  = $(shell printf "\33[37m")
YELLOW = $(shell printf "\33[33m")
RESET  = $(shell printf "\33[0m")
BLUE = $(shell printf "\33[34m")
PURPLE = $(shell printf "\33[35m")
TITLE = $(shell printf "\33[32;40m")

NAME = pipex
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g -Iinclude
LIBFTDIR = libft/
SRC_DIR = srcs/

SRCS = $(wildcard src/*.c)

OBJS = ${SRCS:.c=.o}

INCLUDE = -L ./libft -lft

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@make --silent -C $(LIBFTDIR)
	@${CC} ${FLAGS} ${OBJS} -o ${NAME} ${INCLUDE}
	@echo
	@echo
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

all: ${NAME}

clean:
	@${RM} ${OBJS} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) --silent clean

fclean: clean
	@${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) --silent fclean

re: clean all

.PHONY:	all clean re
