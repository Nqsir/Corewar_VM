/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_to_append.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nerahmou <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/07 18:52:00 by nerahmou     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/12 17:41:30 by nerahmou    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_to_append	*add_to_append(t_to_append *begin, char *str, t_arg_type arg_type)
{
	t_to_append *new;
	t_to_append *tmp;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	new->name = ft_strdup(str);
	new->arg_type = arg_type;
	if (begin)
	{
		tmp = begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		begin = new;
	return (begin);
}

t_to_append	*clear_to_append(t_to_append *begin)
{
	t_to_append	*tmp;

	while (begin)
	{
		tmp = begin->next;
		ft_strdel(&begin->name);
		free(begin);
		begin = tmp;
	}
	return (NULL);
}
