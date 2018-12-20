/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 13:07:40 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	t_session	session;

	if (argc < 2)
		return (!cor_usage());
	if (cor_build_session(&session, argv, argc) &&
				cor_setup(session.mem, session.players,
							session.nb_players, &session.progs))
		cor_play(&session);
	if (session.success && !session.survivors && session.last_alive)
		ft_printf("Player %i(%s) is trop ze best!\n", session.last_alive->id,
					session.last_alive->header.prog_name);
	else if (session.success && session.max_cycles)
		cor_print_mem(&session);
	cor_free(&session);
	return (!session.success);
}
