/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_append_to_res.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 21:46:32 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

unsigned char	*asm_memcatdup(unsigned char *s1, unsigned char *s2,
														int size1, int size2)
{
	unsigned char	*new_str;

	if (!s1 && !s2)
		return ((unsigned char *)ft_strdup(""));
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (!(new_str = malloc(size1 + size2 + 1)))
		return ((void *)ft_error(MALLOC_FAILED, 0));
	ft_memcpy(new_str, s1, size1);
	ft_memcpy(new_str + size1, s2, size2);
	free(s1);
	return (new_str);
}

int				asm_append_str(t_asm *prog, unsigned char *str, int size)
{
	if (!(prog->res = asm_memcatdup(prog->res, str, prog->res_size, size)))
		return (0);
	prog->res_size += size;
	prog->prog_size += size;
	return (1);
}

int				asm_append_mb(t_asm *prog, uint32_t nbr, int size)
{
	size = size > 4 ? 4 : size;
	asm_memrev((unsigned char *)&nbr, size);
	if (!asm_append_str(prog, (unsigned char *)&nbr, size))
		return (0);
	return (size);
}
