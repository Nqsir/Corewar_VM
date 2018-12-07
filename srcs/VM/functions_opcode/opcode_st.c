/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_st.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 10:04:04 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 10:04:04 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		check_st(t_var *data, unsigned int pc)
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
	else if (p_2 == IND_CODE)
		test = p_2;
	if (!(p_1 & REG_CODE) || !(test) || p_3 || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				opcode_st(t_var *data, t_process *p_process)
{

	unsigned char	*tmp_val;
	int 			i;

	tmp_val = (unsigned char *)p_process->registre[data->t_params[1][1]].val;

	if (!check_st(data, p_process->pc) && !ft_params_opcode(data, p_process, 0, 1))
	{
		if (data->t_params[1][1] == 0)
		{
			i = 0;
			while (i < MEM_SIZE)
			{
				data->vm[(data->t_params[0][1] + i) % MEM_SIZE] = (unsigned char)(tmp_val + 1);
				i++;
			}
		}
		else
		{
			p_process->registre[data->t_params[1][1]].val = p_process->registre[data->t_params[1][0]].val;
		}

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