/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_ope.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/16 17:32:27 by amatthys     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:23:42 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		cor_get_int(t_session *session, t_prog *prog, int arg_nb)
{
	int		type;
	int		pc;

	type = prog->instr.arg_types[arg_nb];
	if (type == T_REG)
		return (prog->r[prog->instr.args[arg_nb]]);
	else if (type == T_DIR)
		return (prog->instr.args[arg_nb]);
	pc = cor_pc(prog->pc + (int16_t)prog->instr.args[arg_nb] % IDX_MOD);
	return (cor_read_arg(session->mem, pc, 4, T_DIR));
}

void	cor_write(t_session *session, int pc, int to_write)
{
	int i;

	i = -1;
	while (++i < 4)
		session->mem[(pc + i) % MEM_SIZE] = (to_write >> (3 - i) * 8) & 0xff;
}
