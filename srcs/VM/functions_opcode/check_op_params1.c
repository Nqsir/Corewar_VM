/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_op_params1.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 18:02:26 by vsteyaer     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 18:02:26 by vsteyaer    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				check_ld(t_var *data, unsigned char *pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;
	unsigned char	test;

	test = '\0';
	p_1 = pc[1] >> 6;
	p_2 = (unsigned char)(0x3 & (pc[1] >> 4));
	p_3 = (unsigned char)(0x3 & (pc[1] >> 2));
	p_4 = (unsigned char)(0x3 & pc[1]);
	if (p_1 == DIR_CODE)
		test = p_1;
	else if (p_1 == IND_CODE)
		test = p_1;
	if (!(test) || !(p_2 & REG_CODE) || p_3 || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				check_ldi(t_var *data, unsigned char *pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;
	unsigned char	test;

	test = '\0';
	p_1 = pc[1] >> 6;
	p_2 = (unsigned char)(0x3 & (pc[1] >> 4));
	p_3 = (unsigned char)(0x3 & (pc[1] >> 2));
	p_4 = (unsigned char)(0x3 & pc[1]);
	if (p_2 == REG_CODE)
		test = p_2;
	else if (p_2 == DIR_CODE)
		test = p_2;
	if (!(p_1 & 0x3) || !(test) || !(p_3 & REG_CODE) || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				check_lld(t_var *data, unsigned char *pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;
	unsigned char	test;

	test = '\0';
	p_1 = pc[1] >> 6;
	p_2 = (unsigned char)(0x3 & (pc[1] >> 4));
	p_3 = (unsigned char)(0x3 & (pc[1] >> 2));
	p_4 = (unsigned char)(0x3 & pc[1]);
	if (p_1 == DIR_CODE)
		test = p_1;
	else if (p_1 == IND_CODE)
		test = p_1;
	if (!(test) || !(p_2 & REG_CODE) || p_3 || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				check_lldi(t_var *data, unsigned char *pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;
	unsigned char	test;

	test = '\0';
	p_1 = pc[1] >> 6;
	p_2 = (unsigned char)(0x3 & (pc[1] >> 4));
	p_3 = (unsigned char)(0x3 & (pc[1] >> 2));
	p_4 = (unsigned char)(0x3 & pc[1]);
	if (p_2 == REG_CODE)
		test = p_2;
	else if (p_2 == DIR_CODE)
		test = p_2;
	if (!(p_1 & 0x3) || !(test) || !(p_3 & REG_CODE) || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
