/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_live.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 10:01:10 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 10:01:10 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				opcode_live(t_var *data, t_process *p_process)
{
	size_t	i;

	ft_printf("\n---%s || 0x%x---\n", __func__, data->vm[(p_process->pc + data->op_size) % MEM_SIZE]);
	if (!ft_params_opcode(data, p_process, 4, 0))
	{
		i = 0;
		while (i < data->nb_champion)
		{
			if(data->tab_champion[i].nbr == data->t_params[0][0])
			{
				//ft_printf("champ %i : VIVANT\n", i);
				data->tab_champion[i].nb_live++;
				data->last_live = data->t_params[0][0];
				break;
			}
			i++;
		}
		ft_printf("last live = %i\n", data->last_live);
		p_process->nbr_live++;
		p_process->pc = ((p_process->pc + data->op_size) % MEM_SIZE);
		return (EXIT_SUCCESS);
	}
	p_process->pc = ((p_process->pc + 1) % MEM_SIZE);
	return (EXIT_FAILURE);
}