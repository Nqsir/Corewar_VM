# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/08/13 12:19:28 by amatthys     #+#   ##    ##    #+#        #
#    Updated: 2018/09/05 13:25:05 by jmonneri    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

include ../utils/colors.mk
.PHONY: all clean fclean re signature

NAME = corewar

CC = gcc
CFLAGS += -Wall -Wextra -Werror -g

SRCDIR = ./src/
OBJDIR = ./obj/
INCDIR = ./includes/
COMDIR = ../common/
LFTDIR = $(COMDIR)/libft/
H_FILE = $(INCDIR)corewar.h

INCLUDE = -I $(INCDIR) -I $(COMDIR)includes -I $(LFTDIR)includes

SRC =	input_build_session.c input_setup.c main.c op.c ope01_05.c \
		ope06_10.c ope11_15.c ope16.c play.c play_exec.c play_get.c \
		utils_free.c utils_free_progs.c utils_general.c utils_ope.c \
		utils_players.c utils_print.c utils_progs.c

C_FILES = $(addprefix $(SRCDIR), $(SRC))
O_FILES = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(C_FILES))

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME) | signature

$(NAME): $(OBJDIR) $(O_FILES) $(LFTDIR)libft.a
	@$(CC) $(CFLAGS) -o $(NAME) $(O_FILES) -L$(LFTDIR) -lft

$(LFTDIR)libft.a:
	@make -C $(LFTDIR)

$(OBJDIR):
	@mkdir $@

$(OBJDIR)%.o: $(SRCDIR)%.c $(H_FILE) $(COMDIR)includes/op.h
	@printf %b "0️⃣  $(NAME): Compiling $@ from $<..."
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)
	@printf "\r" && printf "                                                                                                \r"

clean:
	@printf "$(TRED)[X]$(NORMAL) $(NAME): Deleting objects and temporary files... "
	@rm -rf $(OBJDIR)
	@printf "$(TGREEN)[V]$(NORMAL)\n"
	@rm -rf corewar.dSYM
	@make -C $(LFTDIR) clean

fclean: clean
	@printf "$(TRED)[X]$(NORMAL) $(NAME): Deleting $(NAME)... "
	@rm -f $(NAME)
	@printf "$(TGREEN)[V]$(NORMAL)\n"
	@make -C $(LFTDIR) fclean

re: fclean all

signature:
	@echo "$(TCYAN)"
	@echo "   ██████╗ ██████╗ ██████╗ ███████╗██╗    ██╗ █████╗ ██████╗TM"
	@echo "  ██╔════╝██╔═══██╗██╔══██╗██╔════╝██║    ██║██╔══██╗██╔══██╗"
	@echo "  ██║     ██║   ██║██████╔╝█████╗  ██║ █╗ ██║███████║██████╔╝"
	@echo "  ██║     ██║   ██║██╔══██╗██╔══╝  ██║███╗██║██╔══██║██╔══██╗"
	@echo "  ╚██████╗╚██████╔╝██║  ██║███████╗╚███╔███╔╝██║  ██║██║  ██║"
	@echo "   ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝"
	@echo "                       By Amatthys Kevazoul Nerahmou Jmonneri"
	@echo "$(NORMAL)"
