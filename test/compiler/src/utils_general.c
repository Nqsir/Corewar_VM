/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_general.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:04 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:47:02 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		jump_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && ft_isspace(str[i + j]))
		j++;
	return (j);
}

void	asm_memrev(void *ptr, int size)
{
	int				i;
	unsigned char	tmp;
	unsigned char	*mem;

	mem = (unsigned char *)ptr;
	i = -1;
	while (++i < --size)
	{
		tmp = mem[i];
		mem[i] = mem[size];
		mem[size] = tmp;
	}
	return ;
}

int		asm_e(t_asm *prog, char *input, ...)
{
	va_list	ap;
	char	*str;

	va_start(ap, input);
	str = ft_vspf(input, ap);
	ft_fprintf(2, "Error: %s (%s:%i)\n",
		str, prog->s_file, prog->line + 1);
	if (prog->file[prog->line])
		ft_fprintf(2, "\t'%s'\n", prog->file[prog->line]);
	free(str);
	va_end(ap);
	return (0);
}
