/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.42.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/04 19:48:49 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/15 16:52:39 by fablin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstndup(const t_list *lst, size_t n)
{
	t_list	*new;
	t_list	*begin;
	size_t	i;

	i = 0;
	if (lst == NULL || n <= 0)
		return (NULL);
	if ((new = ft_lstnew(lst->content, lst->content_size)) == NULL)
		return (NULL);
	i++;
	begin = new;
	lst = lst->next;
	while (lst && i < n)
	{
		if ((new->next = ft_lstnew(lst->content, lst->content_size)) == NULL)
		{
			ft_lstfree(begin);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
		i++;
	}
	return (begin);
}
