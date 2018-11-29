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
/*
void			*my_memalloc(t_free **lst_free, size_t size)
{
	void		*rep;
	t_free		*link;

	if (!(rep = ft_memalloc(size)))
		ft_printf("erreur memalloc_data\n");
	if (!(link = ft_memalloc(sizeof(t_free))))
	{
		free(rep);
		ft_printf("erreur memalloc_my_free\n");
	}
	if (!(*lst_free))
	{
		ft_printf("============>>>>>>>>>>>>>in?\n");
		link->next = NULL;
		link->prev = NULL;
		link->address = (size_t)rep;
		(*lst_free) = link;
	}
	else
	{
		link->address = (size_t)rep;
		link->next = (*lst_free);
		(*lst_free)->prev = link;
		(*lst_free) = link;

	//	link->address = (size_t)rep;
	//	(*lst_free)->prev = link;
	//	tmp_actu = (*lst_free);
	//	(*lst_free) = (*lst_free)->prev;
	//	(*lst_free)->next = tmp_actu;
	}
	ft_printf("link->address = %x\n", link->address);
	ft_printf("(*lst_free)->prev %s\n", (*lst_free)->prev);
	ft_printf("(*lst_free)->next %s\n", (*lst_free)->next);
	return (rep);
}

int				my_free(t_free **lst_free, size_t address)
{
	t_free	*elem;
	t_free	*elem_prev;
	t_free	*elem_next;

	elem = *lst_free;
	while (elem && elem->address != address)
		elem = elem->next;
	ft_printf("elem->address = %x\n", elem->address);
	if (elem && elem->address == address)
	{
		elem_prev = elem->prev;
		elem_next = elem->next;
		ft_printf("elem_prev %s\n", elem_prev);
		ft_printf("elem_next %s\n", elem_next);
		free((void *)elem->address);
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
*/

t_free     *ft_delfirst(t_free *malist)
{
	t_free *tmp;
	if (malist != NULL)
	{
		tmp = malist;
		tmp = tmp->next;
		free((void *)malist->address);
		free(malist);
		return (tmp);
	}
	return (NULL);
}
t_free     *ft_delend(t_free *malist)
{
	t_free *tmpone;
	t_free *tmptwo;
	if (malist == NULL)
	{
		return (NULL);
	}
	if (malist->next == NULL)
	{
		free((void *)malist->address);
		free(malist);
		return (NULL);
	}
	tmpone = malist;
	tmptwo = malist;
	while (tmpone->next != NULL)
	{
		tmptwo = tmpone;
		tmpone = tmpone->next;
	}
	tmptwo->next = NULL;
	free(tmpone);
	return (malist);
}

t_free		*ft_lstsupdel(t_free *malist, size_t address)
{
	t_free *elem;

	elem = malist;
	while (elem && elem->address != address)
		elem = elem->next;
	if (elem->prev == NULL)
		return (ft_delfirst(malist));
	if (elem->next == NULL)
		return (ft_delend(malist));

	elem->prev->next = elem->next;
	free((void *)elem->address);
	free(elem);
	return(malist);
}

void     *my_memalloc(t_free *malist, size_t address)
{
	t_free *maillon;
	maillon = (t_free*)malloc(sizeof(t_free));
	if (maillon == NULL)
		return (NULL);
	maillon->address = address;
	maillon->next = malist;
	return (maillon);
}
