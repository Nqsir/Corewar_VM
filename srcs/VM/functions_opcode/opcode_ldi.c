/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_ldi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 09:47:47 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 09:47:47 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		check_ldi(t_var *data, unsigned int pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;
	unsigned char	test;

	test = '\0';
	p_1 = data->vm[pc + 1] >> 6;
	p_2 = (unsigned char)(0x3 & (data->vm[pc + 1] >> 4));
	p_3 = (unsigned char)(0x3 & (data->vm[pc + 1] >> 2));
	p_4 = (unsigned char)(0x3 & data->vm[pc + 1]);
	if (p_2 == REG_CODE)
		test = p_2;
	else if (p_2 == DIR_CODE)
		test = p_2;
	if (!(p_1 & 0x3) || !(test) || !(p_3 & REG_CODE) || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				opcode_ldi(t_var *data, t_process *p_process)
{
	unsigned int	tmp_adr;
	unsigned char	tmp_val[4];
	int 			i;

	ft_printf("\n---%s || 0x%x---\n", __func__, data->vm[(p_process->pc + data->op_size) % MEM_SIZE]);
	if (!check_ldi(data, p_process->pc) && !ft_params_opcode(data, p_process, 2, 1))
	{
		tmp_adr = ((data->t_params[0][0] + data->t_params[0][1]) % MEM_SIZE);
		i = 0;
		while (i < MEM_SIZE)
		{
			tmp_val[i] = data->vm[(tmp_adr + i) % MEM_SIZE];
			i++;
		}
		p_process->registre[data->t_params[1][2]].val =	(unsigned int)tmp_val;
		if (p_process->registre[data->t_params[1][2]].val == 0)
			p_process->carry = 1;
		else
			p_process->carry = 0;
		p_process->pc =  ((p_process->pc + data->op_size) % MEM_SIZE);
		return (EXIT_SUCCESS);
	}
	p_process->pc =  ((p_process->pc + 1) % MEM_SIZE);
	return (EXIT_FAILURE);
}