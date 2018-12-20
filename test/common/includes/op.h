/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amatthys <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 10:18:39 by amatthys     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 15:24:21 by nerahmou    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H

# include <inttypes.h>

# define REG_SIZE				1
# define IND_SIZE				2
# define DIR_SIZE				4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			12
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_IND					2
# define T_DIR					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct s_session		t_session;
typedef struct s_prog			t_prog;
typedef char					t_arg_type;

typedef struct					s_header
{
	int							magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	uint32_t					prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

int								live(t_session *session, t_prog *prog);

typedef struct					s_op
{
	char						*cmd;
	int							nb_args;
	t_arg_type					args_type[4];
	int							op_code;
	int							cycles;
	char						*instruction;
	unsigned int				toggle_carry:1;
	unsigned int				use_ind:1;
	unsigned int				octal:1;
	int							(*f)(t_session *session, t_prog *prog);
}								t_op;

#endif
