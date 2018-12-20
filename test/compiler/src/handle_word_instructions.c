/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_word_instructions.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nerahmou <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/04 19:51:31 by nerahmou     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:45:39 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	*get_next_word(void *lst)
{
	return (((t_word*)lst)->next);
}

t_word	*clear_instruction_lst(t_word *lst)
{
	t_word *tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_strdel(&lst->str);
		ft_strdel(&lst->type);
		free(lst);
		lst = NULL;
		lst = tmp;
	}
	return (NULL);
}

t_word	*push_word(t_word *list, char *str)
{
	t_word	*new;
	t_word	*tmp;

	new = ft_memalloc(sizeof(*new));
	new->str = ft_strdup(str);
	if (list)
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		list = new;
	return (list);
}

t_word	*cut_comas(t_word *list, char *str, int *j)
{
	int		pos;
	char	tmp;

	pos = ft_getchar_pos(str, ',');
	if (!pos)
	{
		tmp = str[pos + 1];
		str[pos + 1] = 0;
		list = push_word(list, str);
		str[pos + 1] = tmp;
		*j += 1;
	}
	else
	{
		str[pos] = 0;
		list = push_word(list, str);
		str[pos] = ',';
		*j += pos;
	}
	return (list);
}

t_word	*split_comas(t_word *list, char **instructions)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (instructions[i] && instructions[i][j])
	{
		if (ft_strchr(&instructions[i][j], ',')
				&& ft_strlen(&instructions[i][j]) > 1)
		{
			list = cut_comas(list, &instructions[i][j], &j);
			continue ;
		}
		list = push_word(list, &instructions[i][j]);
		i++;
		j = 0;
	}
	return (list);
}
