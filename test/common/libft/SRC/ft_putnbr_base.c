/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:04 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/17 19:44:04 by kevazoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_putnbr_base(long long nb, int obase)
{
	char *base;

	base = ft_strdup("0123456789abcdef");
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr_base(nb / obase, obase);
	ft_putchar(base[nb % obase]);
	free(base);
}
