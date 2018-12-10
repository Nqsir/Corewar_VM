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
			my_memalloc(&data->lst_free, sizeof(t_process))))
	{
		ft_printf("Erreur create_champion\n");
		return (EXIT_FAILURE);
	}
	data->tab_champion[data->pos_player].nb_live = 0;
	data->tab_champion[data->pos_player].nbr = nbr;
	data->tab_champion[data->pos_player].lst_process->registre[0].val = nbr;
	data->tab_champion[data->pos_player].lst_process->pc =
			((MEM_SIZE/ data->nb_champion) * data->pos_player);
	ft_memcpy(&data->vm[data->tab_champion[data->pos_player].lst_process->pc],
			cor, data->tab_champion[data->pos_player].header.prog_size);
	return (EXIT_SUCCESS);
}