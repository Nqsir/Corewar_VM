/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope11_15.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/13 10:01:03 by amatthys     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 12:35:58 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		cor_sti(t_session *session, t_prog *prog)
{
	int		i;
	int		j;
	int		res;

	j = cor_get_int(session, prog, 1);
	i = cor_get_int(session, prog, 2);
	res = i + j;
	cor_write(session, cor_pc(prog->pc + (res % IDX_MOD)),
			cor_get_int(session, prog, 0));
	return (1);
}

int		cor_fork(t_session *session, t_prog *prog)
{
	int		i;

	i = (short int)prog->instr.args[0];
	cor_add_prog_fork(&session->progs, cor_pc(prog->pc + i % IDX_MOD), prog);
	return (1);
}

int		cor_lld(t_session *session, t_prog *prog)
{
	int		res;
	int		type_0;

	type_0 = prog->instr.arg_types[0];
	if (type_0 == T_DIR || type_0 == T_REG)
		res = cor_get_int(session, prog, 0);
	else
		res = cor_read_arg(session->mem, cor_pc(prog->pc
					+ prog->instr.args[0]), 4, T_DIR);
	prog->r[prog->instr.args[1]] = res;
	prog->carry = (!prog->r[prog->instr.args[1]]);
	return (1);
}

int		cor_lldi(t_session *session, t_prog *prog)
{
	int		i;
	int		j;
	int		reg_nb;
	int		sum;
	int		pc;

	(void)session;
	reg_nb = prog->instr.args[2];
	if (prog->instr.arg_types[0] == T_IND)
		i = cor_read_arg(session->mem, cor_pc(prog->pc +
					prog->instr.args[0] % IDX_MOD), DIR_SIZE, T_DIR);
	else
		i = cor_get_int(session, prog, 0);
	j = cor_get_int(session, prog, 1);
	sum = (i + j);
	pc = prog->pc + sum;
	prog->r[reg_nb] = cor_read_arg(session->mem, cor_pc(pc), DIR_SIZE, T_DIR);
	prog->carry = !prog->r[reg_nb];
	return (1);
}

int		cor_lfork(t_session *session, t_prog *prog)
{
	int		i;

	i = (short int)prog->instr.args[0];
	cor_add_prog_fork(&session->progs, cor_pc(prog->pc + i), prog);
	return (1);
}
