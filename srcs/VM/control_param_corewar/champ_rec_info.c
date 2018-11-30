/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   champ_rec_info.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vsteyaer <vsteyaer@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 14:05:33 by vsteyaer     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 14:05:33 by vsteyaer    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_read_str_champ(int fd, long player_nbr, t_var *data, int pos)
{
	unsigned char		*str;
	ssize_t				ret;

	if (!(str = my_memalloc(&data->lst_free,
			data->tab_champion[pos].header.prog_size + 1)))
		return ;
	if ((ret = read(fd, str, data->tab_champion[pos].header.prog_size))
		!= data->tab_champion[pos].header.prog_size)
		exit(ft_printf("[%d][%d]\n"));
	if (ret > CHAMP_MAX_SIZE)
		exit(ft_printf("(%d bytes > %d bytes)\n"));
	create_champion(data, player_nbr, str);
	/*ft_printf("CHAMP_STR = ");
	write(1, data->tab_champion[data->pos_player].lst_process->program_counter
	, data->tab_champion[pos].header.prog_size);
	ft_printf("\n");*/
	ft_printf("MAGIC = %x\n",
		data->tab_champion[data->pos_player].header.magic);
	ft_printf("PROG_NAME = %s\n",
		data->tab_champion[data->pos_player].header.prog_name);
	ft_printf("SIZE = %u\n",
		data->tab_champion[data->pos_player].header.prog_size);
	ft_printf("COMMENT = %s\n",
		data->tab_champion[data->pos_player].header.comment);
	my_free(&data->lst_free, (size_t)str);
}

static size_t	ft_mem_padding(unsigned int length, unsigned int base)
{
	size_t	res;

	return ((res = length % base) ? (base - res) : 0);
}

static void		ft_r_and_s_magic_name(int fd, t_var *data, int pos)
{
	unsigned char		magic[4 + 1];
	char				p_name[PROG_NAME_LENGTH + 1];

	read(fd, magic, SIZE_INT);
	if ((data->tab_champion[pos].header.magic = ((magic[0] << 24)
			+ (magic[1] << 16) + (magic[2] << 8) + (magic[3])))
				!= COREWAR_EXEC_MAGIC)
		exit(ft_printf("MAUVAIS MAGIC JOHNSON !\n"));
	data->padding = ft_mem_padding(SIZE_INT + PROG_NAME_LENGTH, 8);
	read(fd, p_name, PROG_NAME_LENGTH + data->padding);
	ft_memcpy(data->tab_champion[pos].header.prog_name, p_name, PROG_NAME_LENGTH
		+ data->padding);
}

void			ft_read_dot_cor(char *av, long player_nbr, t_var *data, int pos)
{
	int					fd;
	unsigned char		p_size[4 + 1];
	char				comm[COMMENT_LENGTH + 1];

	if ((fd = open(av, O_RDWR)) < 0)
		exit(ft_printf("wrong file and/or rights\n"));
	ft_r_and_s_magic_name(fd, data, pos);
	read(fd, p_size, SIZE_INT);
	if (ft_limits((char *)p_size, UNSIGNED, INT_MAX))
		exit(ft_printf("La taille de ton prog c'est pas un int !\n"));
	data->tab_champion[pos].header.prog_size = ((p_size[0] << 24)
		+ (p_size[1] << 16) + (p_size[2] << 8) + (p_size[3]));
	data->padding = ft_mem_padding(SIZE_INT + PROG_NAME_LENGTH
		+ (unsigned int)data->padding + SIZE_INT + COMMENT_LENGTH, 16);
	read(fd, comm, COMMENT_LENGTH + data->padding);
	ft_memcpy(data->tab_champion[pos].header.comment, comm, COMMENT_LENGTH
		+ data->padding);
	ft_read_str_champ(fd, player_nbr, data, pos);
}

void			ft_control_player(long player_nbr)
{
	static int		nbr_of_players = 0;

	nbr_of_players++;
	if (nbr_of_players > MAX_PLAYERS)
		exit(ft_printf("This is Corewar NOT SPARTAAAAAAAAAAA\n"));
	if (player_nbr < 0)
		exit(ft_printf("I feel sorry for your parents...\n"));
	if (player_nbr > INT_MAX)
		exit(ft_printf("INT_MAX 2147483647 && INT_MIN -2147483648\n"));
}
