/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isxdigit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/04 19:48:47 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 16:30:40 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_isxdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}
