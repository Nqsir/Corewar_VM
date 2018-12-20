/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_sti.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 10:06:14 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 10:06:14 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		check_sti(t_var *data, unsigned int pc, int dir_oct)
{
	unsigned char	p[3];
	unsigned char	test;
	size_t 			i;

	i = 0;
	test = '\0';
	p[0] = data->vm[((pc + 1) % MEM_SIZE)] >> 6;
	p[1] = (unsigned char)(0x3 & (data->vm[((pc + 1) % MEM_SIZE)] >> 4));
	p[2] = (unsigned char)(0x3 & (data->vm[((pc + 1) % MEM_SIZE)] >> 2));
	data->op_size += 1;
	while (i < 3)
	{
		if (p[i] == REG_CODE)
			data->op_size += 1;
		else if (p[i] == DIR_CODE)
			dir_oct == 2 ? (data->op_size += 2) : (data->op_size += 4);
		else if (p[i] == IND_CODE)
			data->op_size += 2;
		i++;
	}
	if (p[2] == REG_CODE)
		test = p[2];
	else if (p[2] == DIR_CODE)
		test = p[2];
	if ((p[0] != REG_CODE) || !(p[1] & 0x3) || !(test))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				opcode_sti(t_var *data, t_process *p_process)
{
	short			tmp_adr;
	unsigned char	tmp_val[4];
	int 			i;

	if (!check_sti(data, p_process->pc, 2) && !ft_params_opcode(data, p_process, 2, 0))
	{
		tmp_adr = (p_process->pc + (((short)data->t_params[0][1] + (short)data->t_params[0][2]) % IDX_MOD) % MEM_SIZE);
		tmp_val[0] = (unsigned char)((data->t_params[0][0]) >> 24);
		tmp_val[1] = (unsigned char)((data->t_params[0][0]) >> 16);
		tmp_val[2] = (unsigned char)((data->t_params[0][0]) >> 8);
		tmp_val[3] = (unsigned char)(data->t_params[0][0]);
		i = 0;
		if (data->v == 4 || data->v == 6)
		{
			ft_printf("P %4i | sti r%i %i %i\n", p_process->id,
					  (short)data->t_params[1][0], (short)data->t_params[0][1],
					  data->t_params[0][2]);
			ft_printf("       | -> store to %i + %i = %i (with pc and mod %i)\n",
					  (short)data->t_params[0][1], (short)data->t_params[0][2],
					  ((short)data->t_params[0][1] + (short)data->t_params[0][2]), tmp_adr);
		}
		if (tmp_adr < 0)
			tmp_adr = MEM_SIZE + tmp_adr;
		while (i < REG_SIZE)
		{
			data->vm[(tmp_adr + i) % MEM_SIZE] = tmp_val[i];
			i++;
		}
		p_process->pc =  ((p_process->pc + data->op_size) % MEM_SIZE);
		return (EXIT_SUCCESS);
	}
	p_process->pc =  ((p_process->pc + data->op_size) % MEM_SIZE);
	return (EXIT_FAILURE);
}