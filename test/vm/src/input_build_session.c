/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_build_session.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 11:54:43 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int		cor_change_id(t_player **players, t_player *player)
{
	if (player->forced)
		return (cor_e("2 players with the same id"));
	while (cor_get_player_by_id(players, player->id + 1))
		player->id++;
	player->id++;
	return (1);
}

static int		cor_arg_file(t_session *s, int n_id, int n_flag, char *path)
{
	int			default_id;
	t_player	*tmp;

	default_id = 1;
	if (s->nb_players >= MAX_PLAYERS)
		return (cor_e("Too many players (%i players max)", MAX_PLAYERS));
	if (!(s->players[s->nb_players] = ft_memalloc(sizeof(t_player))))
		return (cor_e(MALLOC_FAILED));
	if (n_flag && (tmp = cor_get_player_by_id(s->players, n_id)))
		if (!cor_change_id(s->players, tmp))
			return (0);
	if (!n_flag)
		while (cor_get_player_by_id(s->players, default_id))
			default_id++;
	tmp = s->players[s->nb_players];
	tmp->id = n_flag ? n_id : default_id;
	tmp->forced = n_flag;
	tmp->filename = path;
	s->last_alive = tmp;
	return (++s->nb_players);
}

static int		cor_arg_dump(t_session *session, char *nb)
{
	if (!nb)
		return (cor_usage());
	if (!ft_isalldigit(nb))
		return (cor_usage());
	if ((session->max_cycles = ft_atoi(nb)) <= 0)
		return (cor_usage());
	return (2);
}

static int		cor_process_arg(t_session *session, char **argv, int i)
{
	static int	n_id;
	static int	n_flag;

	if (!ft_strcmp(argv[i], "-v") && argv[i + 1] && ft_isalldigit(argv[i + 1])
		&& (session->v = ft_atoi(argv[i + 1])) && session->v < 32)
		return (2);
	else if (!ft_strcmp(argv[i], "-d") && argv[i + 1])
		return (cor_arg_dump(session, argv[i + 1]));
	else if (!ft_strcmp(argv[i], "-dump") && argv[i + 1] &&
				cor_arg_dump(session, argv[i + 1]) && (session->dump_32 = 1))
		return (2);
	else if (!ft_strcmp(argv[i], "-n") && argv[i + 1] && argv[i + 2] &&
				ft_isalldigit(argv[i + 1]) && !n_flag)
	{
		n_id = ft_atoi(argv[i + 1]);
		n_flag = 1;
		return (2);
	}
	else if (argv[i][0] != '-' &&
			cor_arg_file(session, n_id, n_flag, argv[i]) && !(n_id = 0))
		return (!(n_flag = 0));
	return (argv[i][0] == '-' ? cor_usage() : 0);
}

int				cor_build_session(t_session *session, char **argv, int argc)
{
	int			i;
	int			used_args;

	i = 1;
	used_args = 0;
	ft_bzero(session, sizeof(t_session));
	session->cycles = 1;
	session->survivors = 1;
	if (!(session->players = ft_memalloc(sizeof(argv) * (MAX_PLAYERS + 1))))
		return (cor_e(MALLOC_FAILED));
	while ((i += used_args) < argc)
		if (!(used_args = cor_process_arg(session, argv, i)))
			return (0);
	return (1);
}
