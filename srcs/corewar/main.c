/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fablin <fablin@student.42.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 12:01:55 by fablin       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 17:03:30 by fablin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_read_dot_cor(char *av, long player_nbr, t_var *data)
{
	int		fd;

	if ((fd = open(av, O_RDWR)) < 0)
		exit(ft_printf("wrong file and/or rights\n"));
	//Use GNL
	//parse_champ
	ft_printf("CHAMP [%s] - PLAYER [%d] READY FOR WAR\n", av, player_nbr);
	create_champion(data, "name_dans_.cor", player_nbr, "str_du_champ");
}

static void		ft_control_player(long player_nbr)
{
	static int 		nbr_of_players = 0;

	nbr_of_players++;
	if (nbr_of_players > MAX_PLAYERS)
		exit(ft_printf("This is Corewar NOT SPARTAAAAAAAAAAA\n"));
	if (player_nbr < 0)
		exit(ft_printf("I feel sorry for your parents...\n"));
	if (player_nbr > INT_MAX)
		exit(ft_printf("GROUND-RULES BRO ! INT_MAX 2147483647 && INT_MIN -2147483648\n"));
}

void	ft_check_champ(char **av, long len, int n, t_var *data)
{
	static long		player_nbr = 0;
	long			check_nbr;

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
		ft_read_dot_cor(av[n], player_nbr, data);
	else
		exit(ft_printf("Je te demande un champion, tu m'envoies un lardon... Really ?!?\n"));
	//ft_check_nbr_champ();
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
	ft_printf("FAUT DUUUUUUUUUMMMMMMMMMMMMP : %d\n", ft_atoi(av[n]));
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
			ft_printf("-N ==]==============> DEMACIAAAAAAAAAAAAAA\n");
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

void	ft_print_usage(void)
{
	ft_printf("Usage : ./corewar [-dump nbr_cycles -n number <champion1.cor>");
	ft_printf("-n number <champion2.cor>... -v]\n");
	ft_printf("\t-dump\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-n\t: Champion number\n");
	ft_printf("\t-v\t: Output mode\n");
	exit(EXIT_SUCCESS);
}

void	ft_nbr_champs(int ac, char **av, t_var *data)
{
	int		n;
	long	len;

	n = 1;
	data->nb_champion = 0;
	while (n < ac)
	{
		if ((len = ft_strlen(av[n])) > 4)
		{
			if (((av[n][len - 1]) + (av[n][len - 2] << 8) + (av[n][len - 3]
					<< 16) + (av[n][len - 4] << 24) & 0xFFFFFFFF) == DOT_COR)
				data->nb_champion += 1;
		}
		n++;
	}
	if (data->nb_champion > MAX_PLAYERS || data->nb_champion == 0)
		exit(ft_printf("This is Corewar NOT SPARTAAAAAAAAAAA\n"));
}

void	ft_init_data_corewar(t_var *data)
{
	data->virtual_machine = NULL;
	data->cycle = 0;
	data->check_cycle = 0;
	data->check_cycle_delta = 0;
	data->check_max_check = 0;
	data->nb_live = 0;
	data->nb_champion = 0;
	data->stop_corewar = 0;
	data->dump_value = 0;
}

int		main(int ac, char **av)
{
	t_var	data;

	if (ac == 1)
		ft_print_usage();
	ft_init_data_corewar(&data);
	ft_nbr_champs(ac, av, &data);
	create_vm(&data.virtual_machine, MEM_SIZE);
	ft_printf("data.champ = %d\n", data.nb_champion);
	ft_check_arg(ac, av, &data);
	cycle_management(&data, data.dump_value);
	free(data.virtual_machine);
	return (EXIT_SUCCESS);
}