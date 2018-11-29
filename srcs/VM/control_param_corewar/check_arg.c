/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_arg.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 14:03:57 by vsteyaer     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 14:03:57 by vsteyaer    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	ft_check_champ(char **av, long len, int n, t_var *data)
{
	static long		player_nbr = 0;
	static int 		i = 0;
	long			check_nbr;

	data->pos_player = data->nb_champion - ++i;
	ft_control_player(player_nbr);
	if (len == 2)
	{
		if (!ft_strisdigit_pos_neg(av[n - 1]) || ft_limits(av[n - 1], SIGNED, INT_MAX))
			exit(ft_printf("Come on, #Brain_Install <limits.h> FFS\n"));
		check_nbr = ft_atoi(av[n - 1]);
		len = ft_strlen(av[n]);
		check_nbr >= player_nbr ? (player_nbr = check_nbr) : exit(ft_printf("MAN UP DUDE... [%d] compared to [%d] !\n", check_nbr, player_nbr));
	}
	if (((av[n][len - 1]) + (av[n][len - 2] << 8) + (av[n][len - 3]
			<< 16) + (av[n][len - 4] << 24) & 0xFFFFFFFF) == DOT_COR)
		ft_read_dot_cor(av[n], player_nbr, data, data->pos_player);
	else
		exit(ft_printf("Je te demande un champion, tu m'envoies un lardon... Really ?!?\n"));
	player_nbr++;
}

void	ft_check_visu(int *v)
{
	if (*v > 0)
		exit(ft_printf("One was enough... *That's what she said !* XD\n"));
	*v += 1;
	ft_printf("FAUT L'VISUUUUUUUUUUUU\n");
}

void	ft_check_dump(int n, char **av, int *dump, t_var *data)
{
	long	res;

	res = ft_atoi(av[n]);
	if (*dump > 0)
		exit(ft_printf("One was enough... *That's what she said !* XD\n"));
	if (av[n][0] == '-' || res == 0)
		exit(ft_printf("On t'as demandé de dump la mémoire, pas ton nombre de neurones => [%d] XD\n", res));
	if (!ft_strisdigit_pos_neg(av[n]) || ft_limits(av[n], SIGNED, INT_MAX))
		exit(ft_printf("C'est pas un INT connard !\n"));
	*dump += 1;
	data->dump_value = (unsigned)res;
}

void	ft_check_arg(int ac, char **av, t_var *data)
{
	int		n;
	long	len;
	int		dump;
	int		v;

	n = 1;
	v = 0;
	dump = 0;
	while (n < ac)
	{
		if (!ft_strcmp(av[n], "-dump"))
			ft_check_dump(++n, av, &dump, data);
		else if (!ft_strcmp(av[n], "-v"))
			ft_check_visu(&v);
		else if ((len = ft_strlen(av[n])) > 4)
			ft_check_champ(av, len, n, data);
		else if (!ft_strcmp(av[n], "-n"))
		{
			if (ft_strisdigit_pos_neg(av[++n]))
				ft_check_champ(av, len, ++n, data);
			else
				exit(ft_printf("Toi t'as voulu me faire une Jean-Claude DUSSE apres le -n\n"));
		}
		else
			exit(ft_printf("Mais quel est le gland qui a rentré un mauvais parametre ? LIS L'USAGE PTNNNN\n"));
		n++;
	}
}