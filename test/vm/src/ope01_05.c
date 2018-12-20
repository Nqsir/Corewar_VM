/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope01-05.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 17:57:24 by amatthys     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 16:15:45 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		cor_live(t_session *session, t_prog *prog)
{
	t_player	*player;
	int			i;

	i = prog->instr.args[0];
	player = cor_get_player_by_id(session->players, ft_abs(i));
	if (player && i <= 0)
	{
		session->last_alive = player;
		if (session->v & 0x01)
			ft_printf("Player %d (%s) is said to be alive\n", player->id,
					player->header.prog_name);
	}
	session->nbr_live += 1;
	prog->did_live = 1;
	return (1);
}

int		cor_ld(t_session *session, t_prog *prog)
{
	prog->r[prog->instr.args[1]] = cor_get_int(session, prog, 0);
	prog->carry = (!prog->r[prog->instr.args[1]]);
	return (1);
}

int		cor_st(t_session *session, t_prog *prog)
{
	int16_t		i;

	i = prog->instr.args[1];
	if (prog->instr.arg_types[1] == T_REG)
		prog->r[i] = prog->r[prog->instr.args[0]];
	else
		cor_write(session, cor_pc(prog->pc + (i % IDX_MOD)),
				prog->r[prog->instr.args[0]]);
	return (1);
}

int		cor_add(t_session *session, t_prog *prog)
{
	int		reg_target;
	int		reg_val_1;
	int		reg_val_2;

	(void)session;
	reg_target = prog->instr.args[2];
	reg_val_1 = prog->r[prog->instr.args[0]];
	reg_val_2 = prog->r[prog->instr.args[1]];
	prog->r[reg_target] = reg_val_1 + reg_val_2;
	if (!prog->r[reg_target])
		prog->carry = 1;
	else
		prog->carry = 0;
	return (1);
}

int		cor_sub(t_session *session, t_prog *prog)
{
	(void)session;
	prog->r[prog->instr.args[2]] =
		prog->r[prog->instr.args[0]] - prog->r[prog->instr.args[1]];
	if (!prog->r[prog->instr.args[2]])
		prog->carry = 1;
	else
		prog->carry = 0;
	return (1);
}
