/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_limits.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/17 16:49:44 by vsteyaer     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 16:49:44 by vsteyaer    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int 	ft_limits(char *str, int sign, long long limit)
{
	long long	rev;
	int			ilen;
	int 		clen;
	long 		ret;
	long 		cmp;

	rev = -limit - 1;
	cmp = ft_atoi(str);
	cmp < 0 ? (ret = cmp - rev) : (ret = limit - cmp);
	cmp < 0 ? (ilen = ft_digitlenneg(rev)) : (ilen = ft_digitlen(limit));
	clen = ft_strlen(str);
	if (clen > ilen || str == NULL || limit == 0 || (sign != UNSIGNED
		&& sign != SIGNED) || (sign == UNSIGNED && cmp < 0))
		return (-1);
	else if (clen < ilen)
		return (0);
	if (ret != 0)
	{
		if (ret < 0)
			return (1);
		else
			return(0);
	}
	return (0);
}