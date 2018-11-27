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

int			create_champion(t_var *data, char *name, unsigned int number, char *cor)
{
	static unsigned int 	i = 0;

	if (!(data->tab_champion[i].lst_process = ft_memalloc(sizeof(t_process))))
	{
		ft_printf("Erreur create_champion\n");
		return (EXIT_FAILURE);
	}
	data->tab_champion[i].nb_live = 0;
	data->tab_champion[i].name = ft_strdup(name);
	data->tab_champion[i].number = number;
	data->tab_champion[i].lst_process->registre[0].val = number;
	data->tab_champion[i].lst_process->program_counter = data->virtual_machine + ((MEM_SIZE / data->nb_champion) * i);
	ft_memcpy(data->tab_champion[i].lst_process->program_counter,cor ,ft_strlen(cor));
	i++;
	return (EXIT_SUCCESS);
}
