/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_champion.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/16 18:16:59 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 12:16:12 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			create_champion(t_var *data, unsigned int nbr, unsigned char *cor)
{
	if (!(data->tab_champion[data->pos_player].lst_process =
			ft_memalloc(sizeof(t_process))))
	{
		ft_printf("Erreur create_champion\n");
		return (EXIT_FAILURE);
	}
	data->tab_champion[data->pos_player].nb_live = 0;
	data->tab_champion[data->pos_player].nbr = nbr;
	data->tab_champion[data->pos_player].lst_process
		->registre[0].val = nbr;
	data->tab_champion[data->pos_player].lst_process
		->program_counter = data->virtual_machine + ((MEM_SIZE
				/ data->nb_champion) * data->pos_player);
	ft_memcpy(data->tab_champion[data->pos_player].lst_process
		->program_counter, cor, data->tab_champion[data->pos_player].header
		.prog_size);
	return (EXIT_SUCCESS);
}
