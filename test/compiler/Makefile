# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/09/04 14:13:40 by amatthys     #+#   ##    ##    #+#        #
#    Updated: 2018/09/05 13:24:36 by jmonneri    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

include ../utils/colors.mk
.PHONY: all clean fclean re signature

NAME = asm

CC = gcc
CFLAGS += -Wall -Wextra -Werror -g

SRCDIR = src/
OBJDIR = obj/
INCDIR = includes/
COMDIR = ../common/
LFTDIR = $(COMDIR)libft/
H_FILE = asm.h

INCLUDE = -I $(INCDIR) -I $(COMDIR)includes/ -I $(LFTDIR)includes/

FILES =	analyses \
		build_header \
		dispatch_and_init \
		handle_arguments \
		handle_labels \
		handle_to_append \
		handle_word_instructions \
		main \
		op \
		parse_instructions1 \
		parse_instructions2 \
		process \
		utils_append_to_res \
		utils_free \
		utils_general

SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))


# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME) | signature

$(NAME): $(OBJDIR) $(OBJ) | build_libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LFTDIR) -lft

build_libft:
	@make -C $(LFTDIR)

$(OBJDIR):
	@mkdir $@

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCDIR)$(H_FILE) $(COMDIR)includes/op.h
	@printf %b "0️⃣  $(NAME): Compiling $@ from $<..."
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)
	@printf "\r" && printf "                                                                                             \r"

clean:
	@printf "$(TRED)[X]$(NORMAL) $(NAME): Deleting objects and temporary files... "
	@-rm -rf $(OBJDIR)
	@printf "$(TGREEN)[V]$(NORMAL)\n"
	@-rm -rf asm.dSYM
	@make -C $(LFTDIR) clean

fclean: clean
	@printf "$(TRED)[X]$(NORMAL) $(NAME): Deleting $(NAME)... "
	@-rm -f $(NAME)
	@printf "$(TGREEN)[V]$(NORMAL)\n"
	@-rm -rf cor
	@make -C $(LFTDIR) fclean

re: fclean all

test_asm: all
	@echo "test_asm de $(COR)"
	@./asm ../vm_champs/champs/$(COR).s && mv $(COR).cor cor;
	@./asm_src ../vm_champs/champs/$(COR).s && mv ../vm_champs/champs/$(COR).cor cor/$(COR)\src.cor;
	@diff cor/$(COR).cor cor/$(COR)\src.cor ;
	@cmp -l cor/$(COR).cor cor/$(COR)\src.cor

signature:
	@echo "$(TRED)"
	@echo "   █████╗ ███████╗███╗   ███╗     ██╗ ██████╗  ██╗TM"
	@echo "  ██╔══██╗██╔════╝████╗ ████║    ███║██╔═████╗███║"
	@echo "  ███████║███████╗██╔████╔██║    ╚██║██║██╔██║╚██║"
	@echo "  ██╔══██║╚════██║██║╚██╔╝██║     ██║████╔╝██║ ██║"
	@echo "  ██║  ██║███████║██║ ╚═╝ ██║     ██║╚██████╔╝ ██║"
	@echo "  ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝     ╚═╝ ╚═════╝  ╚═╝"
	@echo "                            Compiling the future !"
	@echo "$(NORMAL)"
