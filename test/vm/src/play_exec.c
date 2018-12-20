/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   play_exec.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 12:27:42 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	cor_attribute_instr(t_prog *prog, int8_t *mem)
{
	if (!prog->instr.cmd && !cor_get_new_instr(mem, prog))
		prog->pc = cor_pc(prog->pc + 1);
}

static void	cor_decrement_left_cycles(t_prog *prog)
{
	if (prog->instr.cmd && prog->instr.left_cycles)
		prog->instr.left_cycles--;
}

static void	cor_exec_instr(t_session *session, t_prog *prog)
{
	if (cor_get_args(&prog->instr, session->mem, prog))
	{
		if (session->v & 0x04 && prog->instr.cmd->op_code != 0x10)
			cor_print_prog(prog);
		if (session->v & 0xf0 &&
				(prog->instr.cmd->op_code != 0x09 || !prog->carry))
			ft_printf("ADV %d (0x%.4x -> 0x%.4x)\n", prog->instr.size,
					prog->pc, cor_pc(prog->pc + prog->instr.size));
		if (session->v & 0xf0
				&& prog->instr.cmd->op_code == 0x09 && prog->carry)
		{
			ft_printf("Jump from 0x%.4x to 0x%.4x\n", prog->pc,
					cor_pc(prog->pc + cor_get_int(session, prog, 0)));
		}
		prog->instr.cmd->f(session, prog);
	}
	prog->pc = cor_pc(prog->pc + prog->instr.size);
	prog->instr.cmd = NULL;
}

void		cor_exec_cycle(t_session *session)
{
	t_prog	*prog;

	prog = session->progs;
	while (prog)
	{
		cor_attribute_instr(prog, session->mem);
		cor_decrement_left_cycles(prog);
		if (prog->instr.cmd && !prog->instr.left_cycles)
			cor_exec_instr(session, prog);
		prog = prog->next;
	}
}
