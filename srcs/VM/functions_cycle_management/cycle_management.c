/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle_management.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 15:48:05 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 18:44:08 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"



static int		init_cycle_management(t_var *data)
{
	data->check_cycle = CYCLE_TO_DIE;
	data->check_max_check = MAX_CHECKS - 1;
	data->check_cycle_delta = CYCLE_TO_DIE;
	data->stop_corewar = 0;
	data->nb_live = 0;
	return (EXIT_SUCCESS);
}

int				cycle_management(t_var *data, unsigned long nb_dump)
{
	init_cycle_management(data);
	while (!data->stop_corewar)
	{
		data->cycle++;
		ft_printf("It is now cycle : %u\n", data->cycle);
		if (data->cycle == data->check_cycle)
			cycle_to_die(data);
		exec_program(data);
		if (nb_dump > 0 && nb_dump == data->cycle)
		{
			print_dump(data);
			data->stop_corewar = 1;
		}
		stop_corewar(data);
	}
	ft_printf("fin normale\n");
	return (EXIT_SUCCESS);
}
