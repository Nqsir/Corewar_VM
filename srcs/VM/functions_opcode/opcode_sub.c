/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_sub.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 10:08:09 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 10:08:09 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		check_sub(t_var *data, unsigned int pc)
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

int				opcode_sub(t_var *data, t_process *p_process)
{
	ft_printf("\n---%s || 0x%x---\n", __func__, data->vm[(p_process->pc + data->op_size) % MEM_SIZE]);
	if (!check_sub(data, p_process->pc) && !ft_params_opcode(data, p_process, 0, 1))
	{
		p_process->registre[data->t_params[1][2]].val =	data->t_params[0][0] - data->t_params[0][1];

		if (p_process->registre[data->t_params[1][2]].val == 0)
			p_process->carry = 1;
		else
			p_process->carry = 0;
		p_process->pc =  ((p_process->pc + data->op_size) % MEM_SIZE);
		ft_printf("reg_val = %i\n", p_process->registre[data->t_params[1][2]].val);
		ft_printf("cary    = %i\n", p_process->carry);
		return (EXIT_SUCCESS);
	}
	p_process->pc =  ((p_process->pc + 1) % MEM_SIZE);
	return (EXIT_FAILURE);
}