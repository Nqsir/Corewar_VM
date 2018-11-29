/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_nbr_champ.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 14:02:04 by vsteyaer     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 14:02:04 by vsteyaer    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	ft_count_nbr_champs(int ac, char **av, t_var *data)
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
	if (data->nb_champion > MAX_PLAYERS)
		exit(ft_printf("This is Corewar NOT SPARTAAAAAAAAAAA\n"));
	if (data->nb_champion == 0)
		exit(ft_printf("ALONE IN THE DARK ISN'T APPROPRIATE HERE !\n"));
}
