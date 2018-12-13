/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opcode_fork.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 09:42:43 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 09:42:43 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				opcode_fork(t_var *data, t_process *p_process, int i)
{
	ft_printf("\n---%s || 0x%x---\n", __func__, data->vm[(p_process->pc + data->op_size) % MEM_SIZE]);
	if (!ft_params_opcode(data, p_process, 2, 0))
	{
		t_process_create(data, p_process, i);
		p_process->pc =  ((p_process->pc + data->op_size) % MEM_SIZE);
		return (EXIT_SUCCESS);
	}
	p_process->pc =  ((p_process->pc + 1) % MEM_SIZE);
	return (EXIT_FAILURE);
}