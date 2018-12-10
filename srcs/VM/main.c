/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 14:08:16 by vsteyaer     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 14:08:16 by vsteyaer    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void		print_t_params(t_var *data)
{
	int n = 0;
	int i;
	ft_printf("| %s |\n", __func__);
	while (n < 2)
	{
		i = 0;
		while (i < 3)
		{
			if (n == 0)
				ft_printf("|  Valeur =\t%x\t|", data->t_params[n][i]);
			if (n == 1)
				ft_printf("|  Registre =\t%x\t|", data->t_params[n][i]);
			i++;
		}
		ft_printf("\n");
		n++;
	}
}

int			ft_indirect(t_var *data, t_process *proc, int dir_oct, int idx)
{
	int 			i;
	unsigned int 	val;

	i = 2;
	val = (data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << 8)
		  + (data->vm[(proc->pc + data->op_size++) % MEM_SIZE]);
	if (idx)
		val = val % IDX_MOD;
	data->t_params[0][data->p_p] = data->vm[(proc->pc + val) % MEM_SIZE];
	data->p_p += 1;
	return (EXIT_SUCCESS);
}

int			ft_direct(t_var *data, t_process *proc, int dir_oct, int idx)
{
	int 			i;
	unsigned int	val;

	i = -1;
	if (dir_oct == 2)
		val = (data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << 8)
			+ (data->vm[(proc->pc + data->op_size++) % MEM_SIZE]);
	else
		val = (data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << 24)
			+ (data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << 16)
			+ (data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << 8)
			+ (data->vm[(proc->pc + data->op_size++) % MEM_SIZE]);
	if (idx)
		val = val % IDX_MOD;
	data->t_params[0][data->p_p] = val;
	data->p_p += 1;
	return (EXIT_SUCCESS);
}

int			ft_registre(t_var *data, t_process *proc, int dir_oct, int idx)
{
	unsigned int	r_num;

	data->t_params[1][data->p_p] = data->vm[(proc->pc + data->op_size) % MEM_SIZE];
	r_num = data->t_params[1][data->p_p];
	if (r_num < 1 || r_num > REG_NUMBER)
		return (EXIT_FAILURE);
	data->t_params[0][data->p_p] = (unsigned int)proc->registre[r_num].val;
	data->p_p += 1;
	data->op_size += 1;
	return (EXIT_SUCCESS);
}

int 		ft_split_params(t_var *data, t_process *proc, int dir_oct,
				int idx)
{
	int 	i;
	int 	err;

	i = 8;
	data->op_size++;
	data->p_p = 0;
	while ((i -= 2))
	{
		err = 0;
		if (!(unsigned char)(0x3 & (data->vm[(proc->pc + 1) % MEM_SIZE] >> i)))
			break ;
		else if ((unsigned char)(0x3 &
			(data->vm[(proc->pc + 1) % MEM_SIZE] >> i)) == REG_CODE)
				err = ft_registre(data, proc, dir_oct, idx);
		else if ((unsigned char)(0x3 &
			(data->vm[(proc->pc + 1) % MEM_SIZE] >> i)) == DIR_CODE)
				err = ft_direct(data, proc, dir_oct, idx);
		else if ((unsigned char)(0x3 &
			(data->vm[(proc->pc + 1) % MEM_SIZE] >> i)) == IND_CODE)
				err = ft_indirect(data, proc, dir_oct, idx);
		if (err != 0)
		{
			ft_printf("Erno ?\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int 		ft_params_opcode(t_var *data, t_process *proc, int dir_oct,
					int idx)
{
	data->op_size++;
	if (data->vm[((proc->pc) % MEM_SIZE)] == 0x0c
		|| data->vm[(proc->pc) % MEM_SIZE] == 0x0f
		|| data->vm[(proc->pc) % MEM_SIZE] == 0x09)
	{
		data->t_params[0][0]
			= ((data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << 8)
			+ data->vm[(proc->pc + data->op_size++) % MEM_SIZE]);
	}
	else if (data->vm[(proc->pc) % MEM_SIZE] == 0x01)
	{
		data->t_params[0][0]
			= ((data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << (OCT * 3))
			+ (data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << (OCT * 2))
			+ (data->vm[(proc->pc + data->op_size++) % MEM_SIZE] << OCT)
			+ data->vm[(proc->pc + data->op_size++) % MEM_SIZE]);
	}
	else
	{
		if (ft_split_params(data, proc, dir_oct, idx))
		{
			data->op_size = 1;
			return (EXIT_FAILURE);
		}
	}
	/*DEBUG-START*/
	print_t_params(data);
	/*DEBUG-END*/
	ft_printf("data->op_size = %d\n", data->op_size);
	return (EXIT_SUCCESS);
}

static void		ft_init_data_corewar(t_var *data)
{
	data->vm = NULL;
	data->cycle = 0;
	data->check_cycle = 0;
	data->check_cycle_delta = 0;
	data->check_max_check = 0;
	data->nb_live = 0;
	data->nb_champion = 0;
	data->stop_corewar = 0;
	data->dump_value = 0;
	data->pos_player = 0;
	data->lst_free = NULL;
	data->p_p = 0;
}

static void		ft_print_usage(void)
{
	ft_printf("Usage : ./corewar [-dump nbr_cycles -n number <champion1.cor>");
	ft_printf("-n number <champion2.cor>... -v]\n");
	ft_printf("\t-dump\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-n\t: Champion number\n");
	ft_printf("\t-v\t: Output mode\n");
	exit(EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	t_var	data;

	if (ac == 1)
		ft_print_usage();
	ft_init_data_corewar(&data);
	ft_count_nbr_champs(ac, av, &data);
	create_vm(&data, &data.vm, MEM_SIZE);
	ft_check_arg(ac, av, &data);
	cycle_management(&data, data.dump_value);
	my_auto_free(&data.lst_free);
	return (EXIT_SUCCESS);
}
