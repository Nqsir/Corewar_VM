#  ************************************************************************** #
#                                                           LE - /            #
#                                                               /             #
#    Makefile                                         .::    .:/ .      .::   #
#                                                  +:+:+   +:    +:  +:+:+    #
#    By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     #
#                                                  #+#   #+    #+    #+#      #
#    Created: 2018/11/08 14:44:31 by vsteyaer     #+#   ##    ##    #+#       #
#    Updated: 2018/11/16 11:46:35 by vsteyaer    ###    #+. /#+    ###.fr      #
#                                                          /                  #
#                                                         /                   #
#  ************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

DIR_SRC_LIBFT = ./libft/srcs/
DIR_INC_LIBFT = ./libft/includes/
DIR_OBJ_LIBFT = ./libft/objs/

DIR_SRC_PRINTF = ./ft_printf/srcs/
DIR_INC_PRINTF = ./ft_printf/includes/
DIR_OBJ_PRINTF = ./ft_printf/objs/

FILES_SRC_LIBFT =  ft_atoi.c \
		           ft_bzero.c \
		           ft_isalnum.c \
		           ft_isalpha.c \
		           ft_isascii.c \
		           ft_isblank.c \
		           ft_iscntrl.c \
		           ft_isdigit.c \
		           ft_isgraph.c \
		           ft_islower.c \
		           ft_isprint.c \
		           ft_isspace.c \
		           ft_isupper.c \
		           ft_isxdigit.c \
		           ft_itoa.c \
		           ft_lstadd.c \
		           ft_lstcat.c \
		           ft_lstdel.c \
		           ft_lstdelone.c \
		           ft_lstdup.c \
		           ft_lstfree.c \
		           ft_lstisalnum.c \
		           ft_lstisalpha.c \
		           ft_lstisdigit.c \
		           ft_lstiter.c \
		           ft_lstlen.c \
		           ft_lstmap.c \
		           ft_lstncat.c \
		           ft_lstndup.c \
		           ft_lstnew.c \
		           ft_lstsplit.c \
		           ft_memalloc.c \
		           ft_memcat.c \
		           ft_memccpy.c \
		           ft_memchr.c \
		           ft_memcmp.c \
		           ft_memcpy.c \
		           ft_memdel.c \
		           ft_memjoin.c \
		           ft_memmove.c \
		           ft_memset.c \
		           ft_putchar.c \
		           ft_putchar_fd.c \
		           ft_putendl.c \
		           ft_putendl_fd.c \
		           ft_putnbr.c \
		           ft_putnbr_fd.c \
		           ft_putstr.c \
		           ft_putstr_fd.c \
		           ft_strcat.c \
		           ft_strchr.c \
		           ft_strclr.c \
		           ft_strcmp.c \
		           ft_strcpy.c \
		           ft_strdel.c \
		           ft_strdup.c \
		           ft_strequ.c \
		           ft_strisalnum.c \
		           ft_strisalpha.c \
		           ft_strisascii.c \
		           ft_strisdigit.c \
		           ft_strisdigit_pos_neg.c \
		           ft_strislower.c \
		           ft_strisprint.c \
		           ft_strisspace.c \
		           ft_strisupper.c \
		           ft_strisxdigit.c \
		           ft_striter.c \
		           ft_striteri.c \
		           ft_strjoin.c \
		           ft_strlcat.c \
		           ft_strlen.c \
		           ft_strmap.c \
		           ft_strmapi.c \
		           ft_strncat.c \
		           ft_strncmp.c \
		           ft_strncpy.c \
		           ft_strndup.c \
		           ft_strnequ.c \
		           ft_strnew.c \
		           ft_strnstr.c \
		           ft_strrchr.c \
		           ft_strsplit.c \
		           ft_strstr.c \
		           ft_strsub.c \
		           ft_strtrim.c \
		           ft_tolower.c \
		           ft_toupper.c \
		           ft_uitoa_base.c \
		           ft_realloc.c \
		           ft_savetext \
		           ft_revstr \
		           ft_revnstr \
		           get_next_line.c

FILES_SRC_PRINTF = ft_b.c \
		           ft_c.c \
		           ft_color.c \
		           ft_conversion.c \
		           ft_d_i.c \
		           ft_gestion.c \
		           ft_lx.c \
		           ft_n.c \
		           ft_o.c \
		           ft_p.c \
		           ft_pourcent.c \
		           ft_printf.c \
		           ft_read_format.c \
		           ft_read_params.c \
		           ft_s.c \
		           ft_switch.c \
		           ft_u.c \
		           ft_wchar.c \
		           ft_x.c

SRC_LIBFT = $(addprefix $(DIR_SRC_LIBFT), $(FILES_SRC_LIBFT))
OBJ_LIBFT = $(addprefix $(DIR_OBJ_LIBFT), $(FILES_SRC_LIBFT:.c=.o))

SRC_PRINTF = $(addprefix $(DIR_SRC_PRINTF), $(FILES_SRC_PRINTF))
OBJ_PRINTF = $(addprefix $(DIR_OBJ_PRINTF), $(FILES_SRC_PRINTF:.c=.o))

all : $(NAME)

$(NAME) :	$(DIR_OBJ_LIBFT) $(OBJ_LIBFT) $(DIR_OBJ_PRINTF) $(OBJ_PRINTF)
			@ar rcs $(NAME) $(OBJ_LIBFT) $(OBJ_PRINTF)
			@echo "\n 💯  LIBFT COMPILED 💯\n"

$(DIR_OBJ_LIBFT):
	@printf "Compilation of \033[1m$(NAME)\033[0m ... ⌛️ "
	@mkdir -p $(DIR_OBJ_LIBFT)

$(DIR_OBJ_PRINTF):
	@mkdir -p $(DIR_OBJ_PRINTF)

$(DIR_OBJ_LIBFT)%.o: $(DIR_SRC_LIBFT)%.c
	gcc $(FLAGS) -I $(DIR_INC_LIBFT) -o $@ -c $<

$(DIR_OBJ_PRINTF)%.o: $(DIR_SRC_PRINTF)%.c
	gcc $(FLAGS) -I $(DIR_INC_PRINTF) -o $@ -c $<

clean:
	@rm -Rf $(DIR_OBJ_LIBFT) $(DIR_OBJ_PRINTF)

fclean : clean
	@rm -Rf $(NAME)
