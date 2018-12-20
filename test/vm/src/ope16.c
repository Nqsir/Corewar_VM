/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope16.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/13 17:31:50 by amatthys     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 12:15:53 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		cor_aff(t_session *session, t_prog *prog)
{
	(void)session;
	(void)prog;
	if (session->v & 0x01)
		ft_putchar((prog->r[prog->instr.args[0]] % 256));
	return (1);
}
