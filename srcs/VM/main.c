/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 14:08:16 by vsteyaer     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 14:08:16 by vsteyaer    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
void 			ft_params_opcode(t_var *data, unsigned char *pc, int dir_oct,
				int idx)
{
	if (idx)
		%IDX_MOD;
	%MEM_SIZE;
}
*/
static void		ft_init_data_corewar(t_var *data)
{
	data->virtual_machine = NULL;
	data->cycle = 0;
	data->check_cycle = 0;
	data->check_cycle_delta = 0;
	data->check_max_check = 0;
	data->nb_live = 0;
	data->nb_champion = 0;
	data->stop_corewar = 0;
	data->dump_value = 0;
	data->pos_player = 0;
	data->lst_free = NULL;
}

static void		ft_print_usage(void)
{
	ft_printf("Usage : ./corewar [-dump nbr_cycles -n number <champion1.cor>");
	ft_printf("-n number <champion2.cor>... -v]\n");
	ft_printf("\t-dump\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-n\t: Champion number\n");
	ft_printf("\t-v\t: Output mode\n");
	exit(EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	t_var	data;

	if (ac == 1)
		ft_print_usage();
	ft_init_data_corewar(&data);
	ft_count_nbr_champs(ac, av, &data);
	create_vm(&data, &data.virtual_machine, MEM_SIZE);
	ft_check_arg(ac, av, &data);
	cycle_management(&data, data.dump_value);
	my_auto_free(&data.lst_free);
	return (EXIT_SUCCESS);
}
