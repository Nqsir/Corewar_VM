/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_process.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 19:19:49 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 19:19:49 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				exec_program(t_var *data)
{
	size_t		i;
	t_process	*p_process;

	i = 0;
	while (i < data->nb_champion)
	{
		p_process = data->tab_champion[i].lst_process;
		while (p_process)
		{
			if (!p_process->flag)
			{
				p_process->flag = 1;
				p_process->end_op = data->cycle + 25 - 1; //data->op_tab[].cycle;
			}
			else if (p_process->end_op == data->cycle)
			{
				ft_printf("        P(%i)\n", p_process->nbr_live);
				p_process->flag = 0;
				p_process->nbr_live++;
				//--------------------------------------------------------------
				//				execution de l'opcode
				//--------------------------------------------------------------
			}
			p_process = p_process->next;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
