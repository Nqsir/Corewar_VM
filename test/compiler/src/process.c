/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:46:22 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

/*
** Traitement des instructions
*/

t_labels	*search_label(char *label_name, t_labels *to_find)
{
	t_labels	*tmp;

	tmp = to_find;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, label_name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			assign_label_value(unsigned char *res, t_labels_to_rep *to_rep,
		t_labels *label)
{
	int	pos_label;
	int	pos_label_to_rep;
	int result;

	pos_label = label->position;
	pos_label_to_rep = to_rep->position;
	result = pos_label - to_rep->debut_instruction;
	asm_memrev((unsigned char *)&result, to_rep->arg_size);
	ft_memcpy(
		&res[sizeof(t_header) + to_rep->position], &result, to_rep->arg_size);
	return (0);
}

int			replace_labels(t_asm *prog)
{
	t_labels			*tmp;
	t_labels_to_rep		*tmp_rep;

	tmp_rep = prog->labels_to_rep;
	while (tmp_rep)
	{
		if (!(tmp = search_label(tmp_rep->name, prog->labels)))
		{
			prog->line = tmp_rep->line;
			return (asm_e(prog, "Label inexistant : ':%s'", tmp_rep->name));
		}
		assign_label_value(prog->res, tmp_rep, tmp);
		tmp_rep = tmp_rep->next;
	}
	return (1);
}

/*
** Parcours de toutes les lignes
** Analyse lexicale et syntaxique de chaque lignes
*/

int			asm_process(t_asm *prog)
{
	char	**epur_comments;
	char	**instructions;
	char	*line;

	while (prog->file[prog->line])
	{
		line = prog->file[prog->line] + jump_spaces(prog->file[prog->line], 0);
		if (ft_strlen(line) && line[0] != COMMENT_CHAR)
		{
			if (!(epur_comments = ft_strsplit(line, COMMENT_CHAR)))
				return (asm_e(prog, MALLOC_FAILED));
			if (!(instructions = ft_split(epur_comments[0], " \t")))
				return (asm_e(prog, MALLOC_FAILED));
			if (!(prog->instruc = split_comas(prog->instruc, instructions)))
				return (asm_e(prog, MALLOC_FAILED));
			ft_free_grid(&epur_comments) && ft_free_grid(&instructions);
			if (!lexicale_analyse(&prog->instruc, prog)
					|| !syntaxe_analyse_and_append(prog))
				return (0);
			prog->instruc = clear_instruction_lst(prog->instruc);
		}
		prog->line++;
	}
	return (!prog->prog_size ? prog->line-- && asm_e(prog, "No instruction")
			: replace_labels(prog));
}
