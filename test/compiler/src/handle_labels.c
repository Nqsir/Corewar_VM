/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_label.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nerahmou <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/04 19:27:35 by nerahmou     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 17:22:25 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int					check_duplicate_label(t_labels *begin, char *name)
{
	t_labels	*tmp;
	int			length;

	tmp = begin;
	while (tmp)
	{
		if (ft_strlen(tmp->name) >= ft_strlen(name))
			length = ft_strlen(tmp->name);
		else
			length = ft_strlen(name) - 1;
		if (!ft_strncmp(tmp->name, name, length))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_labels_to_rep		*add_label_to_replace(t_asm *prog, char *name, int arg_siz,
		int line)
{
	t_labels_to_rep *new;
	t_labels_to_rep *tmp;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	new->name = ft_strdup(name);
	new->debut_instruction = prog->prog_size;
	new->position = prog->prog_size + prog->size_tmp;
	new->arg_size = arg_siz;
	new->line = line;
	tmp = prog->labels_to_rep;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		prog->labels_to_rep = new;
	return (prog->labels_to_rep);
}

t_labels_to_rep		*clear_labels_to_rep(t_labels_to_rep *begin)
{
	t_labels_to_rep	*tmp;

	while (begin)
	{
		tmp = begin->next;
		ft_strdel(&begin->name);
		free(begin);
		begin = tmp;
	}
	return (NULL);
}

t_labels			*add_label(t_labels *begin, char *name, int pos)
{
	t_labels *new;
	t_labels *tmp;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	new->name = ft_strdup(name);
	new->name[ft_strlen(name) - 1] = 0;
	new->position = pos;
	tmp = begin;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		begin = new;
	return (begin);
}

t_labels			*clear_labels(t_labels *begin)
{
	t_labels	*tmp;

	while (begin)
	{
		tmp = begin->next;
		ft_strdel(&begin->name);
		free(begin);
		begin = tmp;
	}
	return (NULL);
}
