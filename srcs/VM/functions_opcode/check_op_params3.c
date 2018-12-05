/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_op_params3.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 18:04:49 by vsteyaer     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 18:04:49 by vsteyaer    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				check_sti(t_var *data, unsigned char *pc)
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
	if (p_3 == REG_CODE)
		test = p_3;
	else if (p_3 == DIR_CODE)
		test = p_3;
	if (!(p_1 & REG_CODE) || !(p_2 & 0x3) || !(test) || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				check_sub(t_var *data, unsigned char *pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;

	p_1 = pc[1] >> 6;
	p_2 = (unsigned char)(0x3 & (pc[1] >> 4));
	p_3 = (unsigned char)(0x3 & (pc[1] >> 2));
	p_4 = (unsigned char)(0x3 & pc[1]);
	if (!(p_1 & REG_CODE) || !(p_2 & REG_CODE) || !(p_3 & REG_CODE) || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				check_xor(t_var *data, unsigned char *pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;

	p_1 = pc[1] >> 6;
	p_2 = (unsigned char)(0x3 & (pc[1] >> 4));
	p_3 = (unsigned char)(0x3 & (pc[1] >> 2));
	p_4 = (unsigned char)(0x3 & pc[1]);
	if (!(p_1 & 0x3) || !(p_2 & 0x3) || !(p_3 & REG_CODE) || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				check_zjmp(t_var *data, unsigned char *pc)
{
	unsigned char	p_1;
	unsigned char	p_2;
	unsigned char	p_3;
	unsigned char	p_4;

	p_1 = pc[1] >> 6;
	p_2 = (unsigned char)(0x3 & (pc[1] >> 4));
	p_3 = (unsigned char)(0x3 & (pc[1] >> 2));
	p_4 = (unsigned char)(0x3 & pc[1]);
	if (!(p_1 & DIR_CODE) || p_2 || p_3 || p_4)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
