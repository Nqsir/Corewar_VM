/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope06_10.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 19:22:12 by amatthys     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 12:34:54 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		cor_and(t_session *session, t_prog *prog)
{
	int	i;
	int	j;

	i = cor_get_int(session, prog, 0);
	j = cor_get_int(session, prog, 1);
	prog->r[prog->instr.args[2]] = i & j;
	prog->carry = (!prog->r[prog->instr.args[2]]);
	return (1);
}

int		cor_or(t_session *session, t_prog *prog)
{
	int	i;
	int	j;

	i = cor_get_int(session, prog, 0);
	j = cor_get_int(session, prog, 1);
	prog->r[prog->instr.args[2]] = i | j;
	prog->carry = (!prog->r[prog->instr.args[2]]);
	return (1);
}

int		cor_xor(t_session *session, t_prog *prog)
{
	int	i;
	int	j;

	i = cor_get_int(session, prog, 0);
	j = cor_get_int(session, prog, 1);
	prog->r[prog->instr.args[2]] = i ^ j;
	prog->carry = (!prog->r[prog->instr.args[2]]);
	return (1);
}

int		cor_zjmp(t_session *session, t_prog *prog)
{
	int	i;

	i = cor_get_int(session, prog, 0);
	if (prog->carry)
		prog->pc = cor_pc(prog->pc - prog->instr.size + (i) % IDX_MOD);
	return (1);
}

int		cor_ldi(t_session *session, t_prog *prog)
{
	int		i;
	int		j;
	int		reg_nb;
	int		sum;
	int		pc_idx;

	(void)session;
	reg_nb = prog->instr.args[2];
	if (prog->instr.arg_types[0] == T_IND)
		i = cor_read_arg(session->mem, cor_pc(prog->pc +
					prog->instr.args[0] % IDX_MOD), DIR_SIZE, T_DIR);
	else
		i = cor_get_int(session, prog, 0);
	j = cor_get_int(session, prog, 1);
	sum = (i + j);
	pc_idx = prog->pc + sum % IDX_MOD;
	prog->r[reg_nb] = cor_read_arg(session->mem,
			cor_pc(pc_idx), DIR_SIZE, T_DIR);
	return (1);
}
