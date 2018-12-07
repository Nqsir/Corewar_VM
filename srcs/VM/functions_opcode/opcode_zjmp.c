/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_zjmp.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 10:11:07 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 10:11:07 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				opcode_zjmp(t_var *data, t_process *p_process)
{
	if (!ft_params_opcode(data, p_process, 2, 0))
	{
		if (p_process->carry == 1)
		{
			p_process->pc = ((p_process->pc + data->t_params[0][0]) % MEM_SIZE);
			return (EXIT_SUCCESS);
		}
		else
		{
			p_process->pc =  ((p_process->pc + 1) % MEM_SIZE);
			return (EXIT_SUCCESS);
		}
	}
	p_process->pc =  ((p_process->pc + 1) % MEM_SIZE);
	return (EXIT_FAILURE);
}