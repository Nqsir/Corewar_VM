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
# define SIZE_INT 4

typedef struct			s_reg
{
	long				val: REG_SIZE * 8;
}						t_reg;

typedef struct			s_free
{
	size_t				address;
	struct s_free		*prev;
	struct s_free		*next;
}						t_free;

typedef struct			s_process
{
	unsigned char		*program_counter;
	unsigned long		nbr_live;
	unsigned long		end_op;
	t_reg				registre[REG_NUMBER];
	int					carry;
	struct s_process	*next;
	struct s_process	*prev;
	int					flag;
}						t_process;

typedef struct			s_champion
{
	int					nbr;
	unsigned long		nb_live;
	t_process			*lst_process;
	t_header			header;
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
	unsigned char		*virtual_machine;
	t_champion			tab_champion[MAX_PLAYERS];
	unsigned long		cycle;
	unsigned long		check_cycle;
	unsigned long		check_cycle_delta;
	unsigned long		check_max_check;
	unsigned int		nb_live;
	unsigned int		nb_champion;
	unsigned long		stop_corewar;
	unsigned long		dump_value;
	size_t				padding;
	unsigned int		pos_player;
	t_op				op_tab[17];
	t_free				*lst_free;
}						t_var;

int						create_vm(unsigned char **virtual_machine,
							size_t size_vm);
int						create_champion(t_var *data, unsigned int number,
							unsigned char *cor);
int						cycle_management(t_var *data, unsigned long nb_dump);
int						cycle_to_die(t_var *data);
int						stop_corewar(t_var *data);
int						exec_program(t_var *data);
int						print_vm(t_var *data);
void					ft_count_nbr_champs(int ac, char **av, t_var *data);
void					ft_check_arg(int ac, char **av, t_var *data);
void					ft_control_player(long player_nbr);
void					ft_read_dot_cor(char *av, long player_nbr, t_var *data,
							int pos);
void					*my_memalloc(t_free *lst_free, size_t size);
//int						my_free(t_free **lst_free, size_t address);
//int						my_auto_free(t_free **lst_free);
//int						my_exit(t_free **lst_free, int num, char *msg);
#endif
