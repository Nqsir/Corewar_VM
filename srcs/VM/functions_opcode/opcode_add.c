/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_add.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/06 16:36:46 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/06 16:36:46 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		check_add(t_var *data, unsigned int pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;

	p_1 = data->vm[pc + 1] >> 6;
	p_2 = (unsigned char)(0x3 & (data->vm[pc + 1] >> 4));
	p_3 = (unsigned char)(0x3 & (data->vm[pc + 1] >> 2));
	p_4 = (unsigned char)(0x3 & data->vm[pc + 1]);
	if (!(p_1 & REG_CODE) || !(p_2 & REG_CODE) || !(p_3 & REG_CODE) || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				opcode_add(t_var *data, t_process *p_process)
{
	if (!check_add(data, p_process->pc) && !ft_params_opcode(data, p_process, 0, 1))
	{
		if (data->v == 4 || data->v == 6)
			ft_printf("P    %i | add r%i r%i r%i\n", p_process->id,
			data->t_params[1][0], data->t_params[1][1], data->t_params[1][2]);
		p_process->registre[data->t_params[1][2]].val =	data->t_params[0][0] + data->t_params[0][1];
		if (p_process->registre[data->t_params[1][2]].val == 0)
			p_process->carry = 1;
		else
			p_process->carry = 0;
		p_process->pc =  ((p_process->pc + data->op_size) % MEM_SIZE);
		return (EXIT_SUCCESS);
	}
	p_process->pc =  ((p_process->pc + data->op_size) % MEM_SIZE);
	return (EXIT_FAILURE);
}
