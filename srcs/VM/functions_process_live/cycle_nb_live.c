/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_vm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fpupier <fpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/16 11:21:44 by fpupier      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 21:25:12 by fpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				t_process_create(t_process **new_process)
{
	if (!(*new_process = ft_memalloc(sizeof(t_process))))
	{
		ft_printf("Erreur t_process_create\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int		t_process_del(t_process **start_process, t_process **actual)
{
	t_process	*p_prev;
	t_process	*p_next;

	p_next = (*actual)->next;
	p_prev = (*actual)->prev;
	if (!p_prev && p_next)
	{
		p_next->prev = NULL;
		*start_process = p_next;
	}
	else if (p_prev && p_next)
	{
		p_next->prev = p_prev;
		p_prev->next = p_next;
	}
	else if (p_prev && !p_next)
		p_prev->next = NULL;
	free(*actual);
	return (EXIT_SUCCESS);
}

static int		update_cycle_process(t_var *data)
{
	size_t		i;
	t_process	*p_process;

	i = 0;
	while (i < data->nb_champion)
	{
		p_process = data->tab_champion[i].lst_process;
		while (p_process)
		{
			p_process->nbr_live = 0;
			p_process = p_process->next;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int		action_cycle_process(t_var *data)
{
	if (data->nb_live >= NBR_LIVE || !data->check_max_check)
	{
		ft_printf("CYCLE_TO_DIE\t[OK]\t: %u\n", data->check_cycle_delta);
		data->check_cycle_delta -= CYCLE_DELTA;
		data->check_cycle += data->check_cycle_delta;
		data->check_max_check = MAX_CHECKS - 1;
	}
	else
	{
		ft_printf("CYCLE_TO_DIE\t[RESTART %i]\t: %u\n", data->check_max_check,
			data->check_cycle_delta);
		data->check_max_check--;
		data->check_cycle += data->check_cycle_delta;
	}
	data->nb_live = 0;
	return (EXIT_SUCCESS);
}

int				cycle_to_die(t_var *data)
{
	size_t		i;
	t_process	*p_process;

	i = 0;
	while (i < data->nb_champion)
	{
		p_process = data->tab_champion[i].lst_process;
		while (p_process)
		{
			if (!p_process->nbr_live)
			{
				t_process_del(&data->tab_champion[i].lst_process, &p_process);
			}
			else
				data->tab_champion[i].nb_live += p_process->nbr_live;
			p_process = p_process->next;
		}
		data->nb_live += data->tab_champion[i].nb_live;
		data->tab_champion[i].nb_live = 0;
		i++;
	}
	action_cycle_process(data);
	update_cycle_process(data);
	return (EXIT_SUCCESS);
}
