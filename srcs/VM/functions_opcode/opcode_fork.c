/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_fork.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 09:42:43 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 09:42:43 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				opcode_fork(t_var *data, t_process *p_process, int i)
{
	if (!ft_params_opcode(data, p_process, 2, 0))
	{
		if (data->v == 4 || data->v == 6)
			ft_printf("P    %i | fork %i (%u)\n", p_process->num,
			data->t_params[0][0],
			p_process->pc + (data->t_params[0][0] % IDX_MOD));
		t_process_create(data, p_process, i);
		p_process->pc = ((p_process->pc + data->op_size) % MEM_SIZE);
		return (EXIT_SUCCESS);
	}
	p_process->pc = ((p_process->pc + 1) % MEM_SIZE);
	return (EXIT_FAILURE);
}