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

static void		ft_check_champ(t_var *data, char **av, long len, int n)
{
	static long		player_nbr = 0;
	static int		i = 0;
	long			check_nbr;

	data->pos_player = data->nb_champion - ++i;
	ft_control_player(data, player_nbr);
	if (len == 2)
	{
		if (!ft_strisdigit_pos_neg(av[n - 1]) || ft_limits(av[n - 1],
				SIGNED, INT_MAX))
			exit(my_exit(&data->lst_free, __FILE__,
				(char *)__func__, __LINE__));
		check_nbr = ft_atoi(av[n - 1]);
		len = ft_strlen(av[n]);
		check_nbr >= player_nbr ? (player_nbr = check_nbr) :
		exit(my_exit(&data->lst_free, __FILE__, (char *)__func__, __LINE__));
	}
	if (((av[n][len - 1]) + (av[n][len - 2] << 8) + (av[n][len - 3]
			<< 16) + (av[n][len - 4] << 24) & 0xFFFFFFFF) == DOT_COR)
		ft_read_dot_cor(av[n], player_nbr, data, data->pos_player);
	else
		exit(my_exit(&data->lst_free, __FILE__, (char *)__func__, __LINE__));
	player_nbr++;
}

static void		ft_check_visu(t_var *data, int *v)
{
	if (*v > 0)
		exit(my_exit(&data->lst_free, __FILE__, (char *)__func__, __LINE__));
	*v += 1;
	//Utiliser visu
}

static void		ft_check_dump(int n, char **av, int *dump, t_var *data)
{
	long	res;

	res = ft_atoi(av[n]);
	if (*dump > 0)
		exit(my_exit(&data->lst_free, __FILE__, (char *)__func__, __LINE__));
	if (av[n][0] == '-' || res == 0)
		exit(my_exit(&data->lst_free, __FILE__, (char *)__func__, __LINE__));
	if (!ft_strisdigit_pos_neg(av[n]) || ft_limits(av[n], SIGNED, INT_MAX))
		exit(my_exit(&data->lst_free, __FILE__, (char *)__func__, __LINE__));
	*dump += 1;
	data->dump_value = (unsigned)res;
}

void			ft_check_arg(int ac, char **av, t_var *data)
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
			ft_check_visu(data, &v);
		else if ((len = ft_strlen(av[n])) > 4)
			ft_check_champ(data, av, len, n);
		else if (!ft_strcmp(av[n], "-n") && av[n + 2])
			ft_strisdigit_pos_neg(av[++n]) ? ft_check_champ(data, av, len, ++n)
			: exit(my_exit(&data->lst_free,
				__FILE__, (char *)__func__, __LINE__));
		else
			exit(my_exit(&data->lst_free, __FILE__,
				(char *)__func__, __LINE__));
		n++;
	}
}