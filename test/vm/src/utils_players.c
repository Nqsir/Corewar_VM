/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_players.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmonneri <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/09 14:08:03 by jmonneri     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:31:30 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

t_player		*cor_get_player_by_id(t_player **players, int id)
{
	int			i;

	i = -1;
	while (players[++i])
		if (players[i]->id == id)
			return (players[i]);
	return (NULL);
}

void			cor_sort_players_by_id(t_player **players)
{
	int			i;
	int			j;
	t_player	*tmp;

	i = -1;
	while (players[++i])
	{
		j = i;
		while (players[++j])
		{
			if (players[j]->id < players[i]->id)
			{
				tmp = players[i];
				players[i] = players[j];
				players[j] = tmp;
			}
		}
	}
}
