/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   my_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 15:34:31 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 15:34:31 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void			*my_memalloc(t_free **lst_free, size_t size)
{
	void		*rep;
	t_free		*link;
	t_free		*tmp_actu;

	if (!(rep = ft_memalloc(size)))
		ft_printf("erreur memalloc_data\n");
	if (!(link = ft_memalloc(sizeof(t_free))))
	{
		free(rep);
		ft_printf("erreur memalloc_my_free\n");
	}
	else
	{
		link->address = (int)&rep;
		(*lst_free)->prev = link;
		tmp_actu = (*lst_free);
		(*lst_free) = (*lst_free)->prev;
		(*lst_free)->next = tmp_actu;
	}
	return (rep);
}

int				my_free(t_free **lst_free, size_t address)
{
	t_free	*elem;
	t_free	*elem_prev;
	t_free	*elem_next;

	elem = *lst_free;
	elem_prev = elem->prev;
	elem_next = elem->next;
	while (elem->address != address && elem)
	{
		elem_prev = elem->prev;
		elem_next = elem->next;
		elem = elem->next;
	}
	if (elem && elem->address == address)
	{
		free(&elem->address);
		elem_prev->next = elem_next;
		elem_next->prev = elem_prev;
		free(elem);
		return (EXIT_SUCCESS);
	}
	ft_printf("erreur my_free\n");
	return (EXIT_FAILURE);
}

int				my_auto_free(t_free **lst_free)
{
	t_free	*start;
	t_free	*tmp_actu;

	start = *lst_free;
	while (start)
	{
		tmp_actu = start;
		start = start->prev;
		free(tmp_actu);
	}
	return (EXIT_SUCCESS);
}

int				my_exit(t_free **lst_free, int num, char *msg)
{
	ft_printf("%s\n", msg);
	my_auto_free(lst_free);
	return (num);
}
