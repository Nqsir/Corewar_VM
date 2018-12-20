/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_print.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:04 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 12:20:08 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static	void	cor_print_arg(t_instr *curr)
{
	int	i;

	i = -1;
	while (curr && ++i < curr->cmd->nb_args)
	{
		if (curr->arg_types[i] == T_REG)
		{
			ft_putchar('r');
			ft_putnbr(curr->args[i] + 1);
		}
		else if (curr->arg_types[i] == T_DIR)
		{
			ft_putchar('%');
			ft_putnbr(curr->args[i]);
		}
		else
			ft_putnbr(curr->args[i]);
		if (i < curr->cmd->nb_args - 1)
			ft_putstr(", ");
	}
}

void			cor_print_prog(t_prog *current)
{
	ft_printf("P%5i | ", current->id);
	if (current->instr.cmd)
		ft_printf("%s  ", current->instr.cmd->cmd);
	cor_print_arg(&current->instr);
	if (current->instr.cmd->op_code == 0x09)
		ft_printf(current->carry ? " OK" : " FAIL");
	ft_printf("\n");
}

static int		cor_print_32(t_session *session)
{
	int i;

	i = 0;
	ft_printf("DUMP:\n0x");
	while (i + 1 < MEM_SIZE)
	{
		ft_printf("%#.4x : ", i);
		ft_printf("%.2hhx ", session->mem[i++]);
		while (i % 32 != 0)
			ft_printf("%.2hhx ", session->mem[i++]);
		ft_putchar('\n');
	}
	return (1);
}

int				cor_print_mem(t_session *session)
{
	int i;

	i = 0;
	if (session->dump_32)
		cor_print_32(session);
	else
	{
		ft_printf("DUMP:\n0x");
		while (i + 1 < MEM_SIZE)
		{
			ft_printf("%#.4x : ", i);
			ft_printf("%.2hhx ", session->mem[i++]);
			while (i % 64 != 0)
				ft_printf("%.2hhx ", session->mem[i++]);
			ft_putchar('\n');
		}
	}
	return (1);
}
