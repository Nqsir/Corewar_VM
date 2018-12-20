/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   analyses.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nerahmou <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/04 19:51:31 by nerahmou     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 11:40:46 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_tab_analyse_lex	*tab_lex(void)
{
	static t_tab_analyse_lex tab[8] = {
		{&is_label, "label", 0},
		{&is_cmd, "cmd", 0},
		{&is_separator, "separator", 0},
		{&is_register, "register", T_REG},
		{&is_direct, "direct", T_DIR},
		{&is_indirect, "indirect", T_IND},
		{NULL, NULL, 0}
	};

	return ((t_tab_analyse_lex *)tab);
}

int					get_bytecode(t_to_append *args, int length)
{
	t_to_append	*tmp;
	int			octal;
	int			arg_type;
	int			i;

	tmp = args;
	octal = 0;
	i = 3;
	while (length-- > 0)
	{
		if (tmp->arg_type == T_REG)
			arg_type = REG_CODE;
		else if (tmp->arg_type == T_DIR)
			arg_type = DIR_CODE;
		else
			arg_type = IND_CODE;
		octal = octal | arg_type;
		octal = octal << 2;
		tmp = tmp->next;
		i--;
	}
	while (i-- > 0)
		octal = octal << 2;
	return (octal);
}

int					check_syntaxe(t_asm *prog, t_word *instruction,
																t_op pattern)
{
	int	nb_args;
	int	i;

	i = -1;
	prog->size_tmp = pattern.octal ? 2 : 1;
	nb_args = pattern.nb_args == 1 ? 1 : pattern.nb_args + 2;
	while (nb_args-- > 0)
	{
		if (!check_arg_type(prog, instruction, pattern, ++i))
			return (0);
		if ((nb_args > 1 && !instruction->next) ||
				(instruction->next && ft_strcmp(instruction->next->str, ",")))
			return (asm_e(prog, "Wrong number of args"));
		if (nb_args > 1)
			instruction = instruction->next->next;
		nb_args--;
	}
	if (instruction->next)
			return (asm_e(prog, "Wrong number of args"));
	asm_append_mb(prog, pattern.op_code, 1);
	if (pattern.octal)
		asm_append_mb(prog, get_bytecode(prog->to_append, pattern.nb_args), 1);
	append_args(prog, pattern.use_ind);
	prog->to_append = clear_to_append(prog->to_append);
	return (1);
}

int					syntaxe_analyse_and_append(t_asm *prog)
{
	t_word	*tmp;
	int		i;

	tmp = prog->instruc;
	i = -1;
	if (!ft_strcmp(tmp->type, "label"))
	{
		if (!check_duplicate_label(prog->labels, tmp->str))
			return (asm_e(prog, "Duplicate label name : '%s'", tmp->str));
		prog->labels = add_label(prog->labels, tmp->str, prog->prog_size);
		tmp = tmp->next;
	}
	while (tmp && g_op_tab[++i].cmd)
		if (!ft_strcmp(g_op_tab[i].cmd, tmp->str))
			return (check_syntaxe(prog, tmp->next, g_op_tab[i]));
	if (tmp)
		return (asm_e(prog, "Syntax error : '%s'", tmp->str));
	return (1);
}

int					lexicale_analyse(t_word **lst, t_asm *prog)
{
	int					i;
	t_word				*tmp;
	t_tab_analyse_lex	*tab;

	tab = tab_lex();
	tmp = *lst;
	while (tmp)
	{
		i = -1;
		while (tab[++i].type)
		{
			if (tab[i].ptr_func(tmp->str))
			{
				tmp->type = ft_strdup(tab[i].type);
				tmp->arg_type = tab[i].arg_type;
				tmp->line = prog->line;
				break ;
			}
		}
		if (!tmp->type)
			return (asm_e(prog, "Lexical error: \"%s\"", tmp->str));
		tmp = tmp->next;
	}
	return (1);
}
