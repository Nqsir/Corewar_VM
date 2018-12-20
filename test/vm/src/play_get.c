/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   play_get.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 14:32:17 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int8_t		cor_get_size(int *arg_t, int code, int use_ind, int arg_nb)
{
	code = (code >> ((3 - arg_nb) * 2)) & 3;
	if (code == DIR_CODE)
	{
		*arg_t = T_DIR;
		return (use_ind ? IND_SIZE : DIR_SIZE);
	}
	if (code == REG_CODE)
	{
		*arg_t = T_REG;
		return (REG_SIZE);
	}
	if (code == IND_CODE)
	{
		*arg_t = T_IND;
		return (IND_SIZE);
	}
	return (0);
}

int					cor_read_arg(int8_t *mem, int pc, int8_t size, int type)
{
	t_number		number;
	int				i;
	uint8_t			num;

	if (type == T_REG)
	{
		num = *(mem + cor_pc(pc));
		if (num && num <= REG_NUMBER)
			return (num - 1);
		else
			return (-1);
	}
	number.nb = 0;
	i = -1;
	while (++i < size && i < 4)
		number.str[i] = *(mem + ((pc + i) % MEM_SIZE));
	ft_memrev(&number, size);
	return (number.nb);
}

int					cor_check_codage(int8_t codage_byte, int nb_args)
{
	int		i;

	i = 4;
	while (--i >= nb_args)
		if ((codage_byte >> ((3 - i) * 2)) & 3)
			return (0);
	return (1);
}

int					cor_get_args(t_instr *instr, int8_t *mem, t_prog *prog)
{
	uint8_t			codage_byte;
	uint8_t			size;
	int				err;
	int				arg;
	int				i;

	err = 0;
	if ((codage_byte = 128) && instr->cmd->octal)
		codage_byte = *(mem + cor_pc(prog->pc + instr->size++));
	i = -1;
	while (++i < instr->cmd->nb_args)
	{
		size = cor_get_size(&(instr->arg_types[i]),
							codage_byte, instr->cmd->use_ind, i);
		if (!(instr->cmd->args_type[i] & instr->arg_types[i]) ||
			((arg = cor_read_arg(mem, cor_pc(prog->pc + instr->size),
			size, instr->arg_types[i])) == -1 && instr->arg_types[i] == T_REG))
			err++;
		instr->size += size;
		instr->args[i] = instr->cmd->use_ind ? (signed short)arg : arg;
	}
	return (!err);
}

int					cor_get_new_instr(int8_t *mem, t_prog *prog)
{
	int8_t			*mem_pc;

	mem_pc = mem + cor_pc(prog->pc);
	if (*mem_pc && (uint8_t)*mem_pc <= 16)
	{
		ft_bzero(&prog->instr, sizeof(t_instr));
		prog->instr.cmd = &g_op_tab[*mem_pc - 1];
		prog->instr.size++;
		prog->instr.left_cycles = prog->instr.cmd->cycles;
		return (1);
	}
	return (0);
}
