/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_instructions2.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nerahmou <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/04 19:51:31 by nerahmou     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:46:15 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int	is_cmd(char *str)
{
	int i;

	i = -1;
	while (g_op_tab[++i].cmd)
		if (!ft_strcmp(g_op_tab[i].cmd, str))
			return (1);
	return (0);
}

int	is_separator(char *str)
{
	return (*str == SEPARATOR_CHAR);
}

int	is_valid_register(char *str)
{
	int len;

	len = ft_strlen(str);
	if (!len || len > 2 || !ft_isdigit(str[0]) || !ft_isdigit(str[len - 1]))
		return (0);
	return (1);
}

int	is_register(char *str)
{
	return (*str == 'r' && is_valid_register(str + 1));
}
