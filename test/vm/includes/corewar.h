/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 18:01:30 by amatthys     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 18:33:14 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"
# include <inttypes.h>

t_op g_op_tab[17];

/*
** Instructions
*/

typedef struct		s_instr
{
	t_op			*cmd;
	int				left_cycles;
	int				size;
	int				args[4];
	int				arg_types[4];
}					t_instr;

/*
** Processus
*/

typedef struct		s_prog
{
	int				pc;
	int				id;
	int				player_id;
	int32_t			r[REG_NUMBER];
	int				carry:1;
	int				did_live;
	t_instr			instr;
	struct s_prog	*next;
}					t_prog;

/*
** Player (necessary to keep track of who's still alive)
*/

typedef struct		s_player
{
	int				id;
	int				forced;
	char			*filename;
	t_header		header;
	char			*code;
}					t_player;

/*
** Master struct
*/

typedef struct		s_session
{
	int				max_cycles;
	int				dump_32:1;
	int				survivors;
	int				success;
	int				decr;
	int				nbr_live;
	int				cycles;
	t_prog			*progs;
	t_player		**players;
	t_player		*last_alive;
	int8_t			mem[MEM_SIZE];
	uint8_t			v;
	uint8_t			nb_players;
}					t_session;

/*
** Int reconstruction
*/

typedef union		u_number
{
	int				nb;
	char			str[4];
}					t_number;

/*
** Input
*/

int					cor_build_session(t_session *session,
					char **argv, int argc);
int					cor_setup(int8_t *mem, t_player **players, int nb_players,
						t_prog **progs);
void				cor_introduce(t_player **players);

/*
** Progs management
*/

t_prog				*cor_add_new_prog(t_prog **progs, int pc, int player);
t_prog				*cor_append_prog_fork(t_prog **progs, int pc,
						t_prog *source);
int					cor_get_args(t_instr *instr, int8_t *mem,
						t_prog *prog);
void				cor_del_prog(t_prog **lst, t_prog *prog);
void				cor_prog_lst_del(t_prog **lst);

/*
** Processing
*/

int					cor_play(t_session *session);
t_prog				*cor_add_prog_fork(t_prog **progs, int pc, t_prog *src);
int					cor_get_new_instr(int8_t *mem, t_prog *prog);
int					cor_read_arg(int8_t *mem, int pc, int8_t size, int type);
void				cor_exec_cycle(t_session *session);

/*
** Utilities
*/

void				cor_free(t_session *session);
long long			cor_e(char *msg, ...);
int					cor_usage(void);
void				cor_sort_players_by_id(t_player **players);
t_player			*cor_get_player_by_id(t_player **players, int id);
int					cor_pc(int pc);
int					cor_print_mem(t_session *session);
void				cor_print_prog(t_prog *prog);

/*
** Instructions
*/

int					cor_live(t_session *session, t_prog *prog);
int					cor_ld(t_session *session, t_prog *prog);
int					cor_st(t_session *session, t_prog *prog);
int					cor_add(t_session *session, t_prog *prog);
int					cor_sub(t_session *session, t_prog *prog);
int					cor_and(t_session *session, t_prog *prog);
int					cor_or(t_session *session, t_prog *prog);
int					cor_xor(t_session *session, t_prog *prog);
int					cor_zjmp(t_session *session, t_prog *prog);
int					cor_ldi(t_session *session, t_prog *prog);
int					cor_sti(t_session *session, t_prog *prog);
int					cor_fork(t_session *session, t_prog *prog);
int					cor_lld(t_session *session, t_prog *prog);
int					cor_lldi(t_session *session, t_prog *prog);
int					cor_lfork(t_session *session, t_prog *prog);
int					cor_aff(t_session *session, t_prog *prog);
int					cor_get_int(t_session *session, t_prog *prog, int i);
void				cor_write(t_session *session, int pc, int to_write);

#endif
