/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_free_progs.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 17:27:05 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static t_prog	*cor_find_prev_prog(t_prog **lst, t_prog *prog)
{
	t_prog		*prev;
	t_prog		*current;

	prev = NULL;
	current = *lst;
	if (current)
		while (current->next && current != prog)
		{
			prev = current;
			current = current->next;
		}
	return (prev);
}

void			cor_del_prog(t_prog **lst, t_prog *prog)
{
	t_prog		*prev;

	if (!prog || !*lst)
		return ;
	if ((prev = cor_find_prev_prog(lst, prog)))
		prev->next = prog->next;
	if (*lst == prog)
		*lst = prog->next;
	ft_memdel((void **)&prog);
}

void			cor_prog_lst_del(t_prog **lst)
{
	t_prog	*current;
	t_prog	*prev;

	if (!*lst)
		return ;
	current = *lst;
	while ((prev = current))
	{
		current = current->next;
		free(prev);
	}
}
