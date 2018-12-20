/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_general.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:04 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 14:09:08 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int			cor_usage(void)
{
	ft_putstr_fd(
			"usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor]\n"
			, 2);
	ft_putstr_fd("-dump: dump the memory state at nbr_cycles cycles ", 2);
	ft_putstr_fd("(64 values by line)\n", 2);
	ft_putstr_fd("-d: same as -dump but 64 values by line (Zaz-like)\n", 2);
	ft_putstr_fd("-v: set the verbose to different levels, can", 2);
	ft_putstr_fd(" be added together\n", 2);
	ft_putstr_fd("\t- 1 : Show lives and aff\n", 2);
	ft_putstr_fd("\t- 2 : Show cycles\n", 2);
	ft_putstr_fd("\t- 4 : Show operations\n", 2);
	ft_putstr_fd("\t- 8 : Show deaths\n", 2);
	ft_putstr_fd("\t- 16 : Show PC movements\n", 2);
	ft_putstr_fd("-n: set the champion id to number\n\t", 2);
	ft_putstr_fd("if missing, set the champion id with next free number\n", 2);
	return (0);
}

long long	cor_e(char *input, ...)
{
	va_list	ap;
	char	*str;

	va_start(ap, input);
	str = ft_vspf(input, ap);
	ft_fprintf(2, "Error: %s\n", str);
	free(str);
	va_end(ap);
	return (0);
}

int			cor_pc(int pc)
{
	while (pc < 0)
		pc += MEM_SIZE;
	return (pc % MEM_SIZE);
}

void		cor_introduce(t_player **player)
{
	ft_printf("Welcome!\nTonight we are honored to host...\n");
	while (*player)
	{
		ft_printf("%s, %i bytes, will be number %i\n    \"%s\"\n\n",
			(*player)->header.prog_name, (*player)->header.prog_size,
			(*player)->id, (*player)->header.comment);
		player++;
	}
	ft_printf("Enjoy the show:\n");
}
