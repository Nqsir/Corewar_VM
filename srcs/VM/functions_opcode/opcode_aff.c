/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_aff.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/06 20:04:58 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/06 20:04:58 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		check_aff(t_var *data, unsigned int pc)
{
	unsigned char	p_1;

	p_1 = data->vm[pc + 1] >> 6;
	if (!(p_1 & REG_CODE))
	{
		data->op_size += 1 + p_1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				opcode_aff(t_var *data, t_process *p_process)
{
	if (!check_aff(data, p_process->pc) && !ft_params_opcode(data, p_process, 0, 1))
	{
		if (data->v == 4 || data->v == 6)
			ft_printf("P %4i| aff %c\n", p_process->id, (data->t_params[0][0] % 256));
		p_process->pc =  ((p_process->pc + data->op_size) % MEM_SIZE);
		return (EXIT_SUCCESS);
	}
	p_process->pc =  ((p_process->pc + p_process->pc) % MEM_SIZE);
	return (EXIT_FAILURE);
}
