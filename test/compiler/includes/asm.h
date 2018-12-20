/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 15:35:30 by nerahmou    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"

/*
** Liste des labels (label:) rencontres
*/

typedef struct					s_labels
{
	char						*name;
	int							position;
	struct s_labels				*next;
}								t_labels;

/*
** Labels utilises en arguments
*/

typedef struct					s_labels_to_replace
{
	char						*name;
	int							debut_instruction;
	int							position;
	int							line;
	t_arg_type					arg_size;
	struct s_labels_to_replace	*next;
}								t_labels_to_rep;

/*
** Liste des mots de l'instruction avec leur type et leurs type d'argument
** Strucure utile pour l'analyse syntaxique.
*/

typedef struct					s_word_instructions
{
	char						*str;
	char						*type;
	int							arg_type;
	int							line;
	struct s_word_instructions	*next;
}								t_word;

/*
** Structure contenant les lexeme a append apres avoir parcouru tous les args
*/

typedef struct					s_to_append
{
	char						*name;
	int							arg_type;
	struct s_to_append			*next;
}								t_to_append;

/*
** Structure permettant de construire le tableau des symboles
*/

typedef struct					s_tab_analyse_lexicale
{
	int							(*ptr_func)(char *str);
	char						*type;
	int							arg_type;
}								t_tab_analyse_lex;

/*
** Programme assembleur
*/

typedef struct					s_asm
{
	char						*filename;
	char						*s_file;
	char						**file;
	unsigned char				*res;
	char						*error;
	char						*last_line;
	int							res_size;
	int							size_tmp;
	int							prog_size;
	int							line;
	t_header					*header;
	t_labels					*labels;
	t_labels_to_rep				*labels_to_rep;
	t_word						*instruc;
	t_to_append					*to_append;
}								t_asm;

/*
** Session : contient tous les programmes assembleur
*/

typedef struct					s_session
{
	unsigned int				success:1;
	int							files_count;
	char						**filenames;
	t_asm						**asms;
}								t_session;

t_op g_op_tab[17];

/*
** Processing
*/

int								asm_dispatch(t_session *session);
int								asm_build_header(t_asm *prog);
int								asm_process(t_asm *prog);

/*
** Utilities
*/

void							asm_memrev(void *mem, int size);
void							asm_free(t_session *session);
void							asm_free_asm(t_asm **prog);
void							asm_free_asm_array(t_asm ***asms);
int								asm_append_mb(t_asm *prog, uint32_t nbr,
		int size);
int								asm_append_str(t_asm *prog, unsigned char *str,
		int size);
int								asm_e(t_asm *prog, char *msg, ...);
int								jump_spaces(char *str, int i);

t_labels						*clear_labels(t_labels *begin);
t_labels_to_rep					*clear_labels_to_rep(t_labels_to_rep *begin);
t_to_append						*clear_to_append(t_to_append *begin);
t_word							*clear_instruction_lst(t_word *lst);

/*
** Instructions
*/

t_word							*split_comas(t_word *lst, char **instructions);
void							*get_next_word(void *lst);
int								lexicale_analyse(t_word **lst, t_asm *prog);
int								syntaxe_analyse_and_append(t_asm *prog);
int								check_syntaxe(t_asm *prog, t_word *instruction,
		t_op pattern);

t_labels						*add_label(t_labels *beg, char *name, int pos);
t_labels_to_rep					*add_label_to_replace(t_asm *prog, char *name,
		int arg_size, int line);
t_to_append						*add_to_append(t_to_append *begin, char *str,
		t_arg_type arg_size);
int								check_duplicate_label(t_labels *begin,
		char *name);
int								check_arg_type(t_asm *prog, t_word *instru,
		t_op pattern, int i);
int								append_args(t_asm *prog, int is_indirect);

int								is_label(char *str);
int								is_cmd(char *str);
int								is_separator(char *str);
int								is_register(char *str);
int								is_direct(char *str);
int								is_indirect(char *str);
int								is_comment(char *str);

#endif
