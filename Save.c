//
// Created by Victor Steyaert on 09/12/2018.
//

#include "corewar.h"

int			ft_indirect(t_var *data, t_process *proc, int dir_oct, int idx)
{
	int 			i;
	unsigned int 	val;

	i = 2;
	while (--i >= 0)
		val = data->vm[(proc->pc + data->op_size) % MEM_SIZE] << (OCT * i);
	if (idx)
		val = val % IDX_MOD;
	data->t_params[0][data->p_p] = data->vm[(proc->pc + val) % MEM_SIZE];
	data->p_p += 1;
	data->op_size += 2;
	return (EXIT_SUCCESS);
}

int			ft_direct(t_var *data, t_process *proc, int dir_oct, int idx)
{
	int 			i;
	unsigned int	val;

	dir_oct == 2 ? (i = 2) : (i = 4);
	while (--i >= 0)
		val = data->vm[(proc->pc + data->op_size) % MEM_SIZE] << (OCT * i);
	if (idx)
		val = val % IDX_MOD;
	data->t_params[0][data->p_p] = val;
	data->p_p += 1;
	data->op_size += dir_oct;
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

	i = 6;
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
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int 		ft_params_opcode(t_var *data, t_process *proc, int dir_oct,
							int idx)
{
	data->op_size = 1;
	if (data->vm[((proc->pc) % MEM_SIZE)] == 0x0c
		|| data->vm[(proc->pc) % MEM_SIZE] == 0x0f
		|| data->vm[(proc->pc) % MEM_SIZE] == 0x09)
	{
		data->t_params[0][0]
				= ((data->vm[(proc->pc + 1) % MEM_SIZE] << 8)
				   + data->vm[(proc->pc + 2) % MEM_SIZE]);
		data->op_size += 2;
	}
	else if (data->vm[(proc->pc) % MEM_SIZE] == 0x01)
	{
		data->t_params[0][0]
				= ((data->vm[(proc->pc + 1) % MEM_SIZE] << (OCT * 3))
				   + (data->vm[(proc->pc + 2) % MEM_SIZE] << (OCT * 2))
				   + (data->vm[(proc->pc + 3) % MEM_SIZE] << OCT)
				   + data->vm[(proc->pc + 4) % MEM_SIZE]);
		data->op_size += 4;
	}
	else
	{
		if (!ft_split_params(data, proc, dir_oct, idx))
		{
			data->op_size = 1;
			return (EXIT_FAILURE);
		}
	}
	/*DEBUG-START*/
	int n = 0;
	int i;
	while (n < 2)
	{
		i = 0;
		while (i < 4)
		{
			ft_printf("data->t_params[%d][%] = %d\n", n, i,
					  data->t_params[n][i]);
			i++;
		}
		n++;
	}
	/*DEBUG-END*/
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
	unsigned char test[5];

	test[0] = 1;
	test[1] = 1;
	test[2] = 2;
	test[3] = 3;
	test[4] = 4;
	if (ac == 1)
		ft_print_usage();
	ft_init_data_corewar(&data);
	ft_params_opcode(&data, 0, 2, 1);
	ft_count_nbr_champs(ac, av, &data);
	create_vm(&data, &data.vm, MEM_SIZE);
	ft_check_arg(ac, av, &data);
	cycle_management(&data, data.dump_value);
	my_auto_free(&data.lst_free);
	return (EXIT_SUCCESS);
}