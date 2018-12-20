/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   play.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 20:23:51 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	cor_check_alive(t_session *session, t_prog **progs)
{
	int			alive_count;
	t_prog		*prog;
	t_prog		*next;

	next = *progs;
	alive_count = 0;
	while ((prog = next))
	{
		next = prog->next;
		if (!prog->did_live)
		{
			if (session->v & 0x08)
				ft_printf("Process %d did not survive\n", prog->id);
			cor_del_prog(progs, prog);
		}
		else if (++alive_count)
			prog->did_live -= 1;
	}
	if (session->v & 0x08)
		ft_printf("Cycle to die is now %d\n",
			CYCLE_TO_DIE - (session->decr * CYCLE_DELTA));
	session->survivors = alive_count;
	return (alive_count);
}

static int	cor_check_alive_and_decr(t_session *session, int *last_check)
{
	if (!cor_check_alive(session, &session->progs))
		return (1);
	if (++*last_check == MAX_CHECKS || session->nbr_live >= NBR_LIVE)
	{
		*last_check = 0;
		session->decr++;
	}
	session->nbr_live = 0;
	return (0);
}

static int	cor_ctd(int nb_decr)
{
	int res;

	res = CYCLE_TO_DIE - nb_decr * CYCLE_DELTA;
	return (res > 0 ? res : 0);
}

int			cor_play(t_session *session)
{
	int		cycle;
	int		last_check;

	last_check = 0;
	session->success = 1;
	while (cor_ctd(session->decr))
	{
		cycle = 0;
		while (cycle < cor_ctd(session->decr))
		{
			if (session->v & 0x02)
				ft_printf("It is now cycle  %d\n", session->cycles);
			cor_exec_cycle(session);
			if (++cycle == cor_ctd(session->decr) &&
					cor_check_alive_and_decr(session, &last_check))
				return (1);
			if (++session->cycles > session->max_cycles && session->max_cycles)
				return (1);
		}
	}
	session->survivors = 0;
	return (1);
}
