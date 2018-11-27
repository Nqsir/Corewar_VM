/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fablin <fablin@student.42.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 12:02:53 by fablin       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 15:41:12 by fablin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include <fcntl.h>
# define DOT_COR 778268530

typedef struct			s_reg
{
	long				val: REG_SIZE * 8;
}						t_reg;

typedef struct			s_process
{
	char				*program_counter;
	unsigned long		nbr_live;
	unsigned long		end_op;
	t_reg				registre[REG_NUMBER];
	int					carry;
	struct s_process	*next;
	struct s_process	*prev;
	int 				flag;
}						t_process;

typedef struct			s_champion
{
	char				*name;
	int					number;
	unsigned long		nb_live;
	t_process			*lst_process;
}						t_champion;

typedef struct			s_op
{
	char				*name;
	int					val_1;
	int					param[3];
	int					val_2;
	unsigned long		cycle;
	char				*comment;
	int					val_4;
	int					val_5;
}						t_op;

typedef struct			s_var
{
	char				*virtual_machine;
	t_champion			tab_champion[MAX_PLAYERS];
	unsigned long		cycle;
	unsigned long		check_cycle;
	unsigned long		check_cycle_delta;
	unsigned long		check_max_check;
	unsigned int		nb_live;
	unsigned int		nb_champion;
	unsigned long		stop_corewar;
	unsigned long		dump_value;
	t_op				op_tab[17];
}						t_var;

int						create_vm(char **virtual_machine, size_t size_vm);
int						create_champion(t_var *data, char *name, unsigned int number, char *cor);

int						cycle_management(t_var *data, unsigned long nb_dump);
int						cycle_to_die(t_var *data);
int						stop_corewar(t_var *data);
int						exec_program(t_var *data);


int						print_vm(t_var *data);
#endif