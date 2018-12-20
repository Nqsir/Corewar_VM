/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_arguments.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nerahmou <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 17:05:15 by nerahmou     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 20:23:00 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		append_args(t_asm *prog, int is_indirect)
{
	t_to_append	*tmp;
	int			arg_size;

	tmp = prog->to_append;
	while (tmp)
	{
		if (tmp->arg_type == T_REG)
			asm_append_mb(prog, ft_atoi(tmp->name), REG_SIZE);
		else
		{
			arg_size = (tmp->arg_type == T_DIR && !is_indirect)
				? DIR_SIZE : IND_SIZE;
			asm_append_mb(prog, ft_atoi(tmp->name), arg_size);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		get_arg(t_asm *prog, t_word *instruction, t_op pattern, int type)
{
	int		var_size;
	int		dir_char;
	char	*str;

	str = instruction->str;
	var_size = (!pattern.use_ind && type == T_DIR) ? DIR_SIZE : IND_SIZE;
	dir_char = str[0] == DIRECT_CHAR ? 1 : 0;
	if (type == T_REG)
	{
		prog->to_append = add_to_append(prog->to_append, str + 1, REG_SIZE);
		return (REG_SIZE);
	}
	if (ft_strchr(str, LABEL_CHAR))
	{
		prog->to_append = add_to_append(prog->to_append, "", type);
		prog->labels_to_rep = add_label_to_replace(
				prog, str + dir_char + 1, var_size, instruction->line);
	}
	else
		prog->to_append = add_to_append(prog->to_append, str + dir_char, type);
	return (var_size);
}

int		check_arg_type(t_asm *prog, t_word *instruction, t_op pattern, int i)
{
	int		arg_type;
	char	*type;

	if (!instruction)
		return (asm_e(prog, "Wrong number of args, expected : "));
	arg_type = instruction->arg_type & pattern.args_type[i];
	if (!arg_type)
	{
		if (pattern.args_type[i] & T_DIR)
			type = "T_DIR";
		else if (pattern.args_type[i] & T_IND)
			type = "T_IND";
		else
			type = "T_REG";
		return (asm_e(prog, "Wrong type of args : '%s' expected (%s)",
					instruction->str, type));
	}
	prog->size_tmp += get_arg(prog, instruction, pattern, arg_type);
	return (1);
}
