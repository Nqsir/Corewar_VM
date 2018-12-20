/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_progs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 16:16:09 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static t_prog	*cor_new_prog(int pc, int player)
{
	t_prog		*prog;
	static int	nb = 1;

	if (!(prog = ft_memalloc(sizeof(t_prog))))
		return ((void *)(long)cor_e(MALLOC_FAILED));
	prog->r[0] = -ft_abs(player);
	prog->id = nb++;
	prog->player_id = ft_abs(player);
	prog->pc = pc;
	return (prog);
}

static t_prog	*cor_add_prog(t_prog **progs, t_prog *new)
{
	t_prog	*current;

	if (!*progs)
		return ((*progs = new));
	else
	{
		current = *progs;
		new->next = current;
		return ((*progs = new));
	}
}

t_prog			*cor_add_new_prog(t_prog **progs, int pc, int player)
{
	t_prog	*new;

	if (!(new = cor_new_prog(pc, player)))
		return (NULL);
	cor_add_prog(progs, new);
	return (*progs);
}

t_prog			*cor_add_prog_fork(t_prog **progs, int pc, t_prog *src)
{
	t_prog	*dst;
	int		i;

	i = -1;
	if (!(dst = cor_new_prog(cor_pc(pc), src->player_id)))
		return ((void *)(long)cor_e(MALLOC_FAILED));
	while (++i < REG_NUMBER)
		dst->r[i] = src->r[i];
	dst->carry = src->carry;
	dst->did_live = src->did_live;
	cor_add_prog(progs, dst);
	return (*progs);
}
