/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_free.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:30:04 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	cor_free_players(t_player **players)
{
	int i;

	i = -1;
	while (players[++i])
	{
		if (players[i]->code)
			free(players[i]->code);
		free(players[i]);
	}
	free(players);
}

void		cor_free(t_session *session)
{
	if (session->players)
		cor_free_players(session->players);
	if (session->progs)
		cor_prog_lst_del(&session->progs);
}
