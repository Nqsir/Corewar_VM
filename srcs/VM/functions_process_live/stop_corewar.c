/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stop_corewar.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 09:11:18 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 09:11:18 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				stop_corewar(t_var *data)
{
	size_t			i;
	unsigned long	nb_proces;

	i = 0;
	nb_proces = 0;
	while (i < data->nb_champion)
	{
		if (data->tab_champion[i].lst_process)
			nb_proces++;
		i++;
	}
	//ft_printf("cycle_delta = %i || check_cycle_delta = %i\n", CYCLE_DELTA, data->check_cycle_delta);
	if (nb_proces == 0)
		data->stop_corewar = 1;
	return (EXIT_SUCCESS);
}
