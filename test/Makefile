# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jmonneri <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/08/09 18:13:46 by jmonneri     #+#   ##    ##    #+#        #
#    Updated: 2018/09/05 12:34:01 by jmonneri    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re signature
NAME = corewar

CC = gcc -g
CFLAGS += -Wall -Wextra -Werror

LFTDIR = libft
ASM_DIR = compiler
VM_DIR = vm
H_FILE = op.h

# **************************************************************************** #
#                                    PLAYERS                                   #
# **************************************************************************** #

PATH_COR = ./script/cor/
PATH_S = ./vm_champs/
P1 = aurollan.cor
P2 = aurollan.cor

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): build_libft build_asm build_corewar
	@echo "$(NAME) ready, enjoy!"

build_corewar:
	@make -C $(VM_DIR)
	@cp $(VM_DIR)/corewar .

build_asm:
	@make -C $(ASM_DIR)
	@cp $(ASM_DIR)/asm .

build_libft:
	@make -C common/$(LFTDIR)

clean:
	@make -C $(ASM_DIR) clean
	@make -C $(VM_DIR) clean

fclean:
	@make -C $(ASM_DIR) fclean
	@make -C $(VM_DIR) fclean
	@touch asm corewar
	@rm asm corewar

re: fclean all

# **************************************************************************** #
#                                    UTILS                                     #
# **************************************************************************** #

script: #build_corewar
	@sh utils/script/run.sh

valgrind_vm: build_corewar
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./corewar $(addprefix $(PATH_COR), $(P1) $(P2) $(P3) $(P4))
	@rm -rf corewar.dSYM

valgrind_asm: build_asm
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./asm  $(addprefix $(PATH_S), $(P1) $(P2) $(P3) $(P4))
	@rm -rf asm.dSYM

coffee:
	@echo "                       ."
	@echo "                        \`:."
	@echo "                          \`:."
	@echo "                  .:'     ,::"
	@echo "                 .:'      ;:'"
	@echo "                 ::      ;:'"
	@echo "                  :    .:'"
	@echo "                   \`.  :."
	@echo "          _________________________"
	@echo "         : _ _ _ _ _ _ _ _ _ _ _ _ :"
	@echo "     ,---:\".\".\".\".\".\".\".\".\".\".\".\".\":"
	@echo "    : ,'\"\`::.:.:.:.:.:.:.:.:.:.:.::'"
	@echo "    \`.\`.  \`:-===-===-===-===-===-:'"
	@echo "      \`.\`-._:                   :"
	@echo "       \`-.__\`.               ,'"
	@echo "    ,--------\`\"\`-------------'--------."
	@echo "     \`\"--.__                   __.--\"'"
	@echo "             \`\"\"-------------\"\"'"
