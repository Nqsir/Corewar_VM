/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_instructions1.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nerahmou <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/04 19:51:31 by nerahmou     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:46:01 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int	is_valid_label(char *str, char *limit)
{
	while (str != limit)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			return (0);
		str++;
	}
	return (1);
}

int	is_label(char *str)
{
	char *limit;

	limit = NULL;
	limit = ft_strrchr(str, LABEL_CHAR);
	if (!limit)
		return (0);
	if (!is_valid_label(str, limit))
		return (0);
	if (ft_strlen(limit) > 1)
		return (0);
	return (1);
}

int	is_direct(char *str)
{
	if (*str != DIRECT_CHAR)
		return (0);
	return (ft_isalldigit(str + 1)
			|| (str[1] == LABEL_CHAR
				&& is_valid_label(str + 2, &str[ft_strlen(str)])));
}

int	is_indirect(char *str)
{
	if (ft_isalldigit(str))
		return (1);
	return (str[0] == LABEL_CHAR
			&& is_valid_label(str + 1, &str[ft_strlen(str)]));
}
