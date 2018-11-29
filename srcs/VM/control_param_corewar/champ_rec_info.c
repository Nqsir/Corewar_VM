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
	int 				ret;

	if (!(str = ft_memalloc(data->tab_champion[pos].header.prog_size + 1)))
		return ;
	if ((ret = read(fd, str, data->tab_champion[pos].header.prog_size)) != data->tab_champion[pos].header.prog_size)
		exit(ft_printf("Champ code size : [%d] is not prog_size : [%d]\n", ret, data->tab_champion[pos].header.prog_size));
	if (ret > CHAMP_MAX_SIZE)
		exit(ft_printf("File vm_champs/champs/42.cor has too large a code (%d bytes > %d bytes)\n", data->tab_champion[pos].header.prog_size, CHAMP_MAX_SIZE));
	create_champion(data, player_nbr, str);
	//ft_printf("CHAMP_STR = ");
	//write(1, data->tab_champion[data->pos_player].lst_process->program_counter, data->tab_champion[pos].header.prog_size);
	//ft_printf("\n");
}

static size_t	ft_mem_padding(unsigned int length, unsigned int base)
{
	size_t	res;

	return ((res = length % base) ? (base - res) : 0);
}

void			ft_read_dot_cor(char *av, long player_nbr, t_var *data, int pos)
{
	int					fd;
	unsigned char		str1[4 + 1];
	char				str2[PROG_NAME_LENGTH + 1];
	unsigned char		str3[4 + 1];
	char				str4[COMMENT_LENGTH + 1];

	if ((fd = open(av, O_RDWR)) < 0)
		exit(ft_printf("wrong file and/or rights\n"));

	read(fd, str1, SIZE_INT);
	if (((str1[0] << 24) + (str1[1] << 16) + (str1[2] << 8) + (str1[3])) != COREWAR_EXEC_MAGIC)
		exit(ft_printf("MAUVAIS MAGIC JOHNSON !\n"));
	data->tab_champion[pos].header.magic = ((str1[0] << 24) + (str1[1] << 16) + (str1[2] << 8) + (str1[3]));


	data->padding = ft_mem_padding(SIZE_INT + PROG_NAME_LENGTH, 8);
	read(fd, str2, PROG_NAME_LENGTH + data->padding);
	ft_memcpy(data->tab_champion[pos].header.prog_name, str2, PROG_NAME_LENGTH + data->padding);


	read(fd, str3, SIZE_INT);
	if (ft_limits((char *)str3, UNSIGNED, INT_MAX))
		exit(ft_printf("La taille de ton prog c'est pas un int !\n"));
	data->tab_champion[pos].header.prog_size = ((str3[0] << 24) + (str3[1] << 16) + (str3[2] << 8) + (str3[3]));


	data->padding = ft_mem_padding(SIZE_INT + PROG_NAME_LENGTH + data->padding + SIZE_INT + COMMENT_LENGTH, 16);
	read(fd, str4, COMMENT_LENGTH + data->padding);
	ft_memcpy(data->tab_champion[pos].header.comment, str4, COMMENT_LENGTH + data->padding);

	//DEBUUUUUUUUUUUUUUUUUUUUUUUGGGGGG
	ft_printf("MAGIC = %x\n", data->tab_champion[data->pos_player].header.magic);
	ft_printf("PROG_NAME = %s\n", data->tab_champion[data->pos_player].header.prog_name);
	ft_printf("SIZE = %u\n", data->tab_champion[data->pos_player].header.prog_size);
	ft_printf("COMMENT = %s\n", data->tab_champion[data->pos_player].header.comment);
	//DEBUUUUUUUUUUUUUUUUUUUUUUUGGGGGG
	ft_read_str_champ(fd, player_nbr, data, pos);
}

void			ft_control_player(long player_nbr)
{
	static int 		nbr_of_players = 0;

	nbr_of_players++;
	if (nbr_of_players > MAX_PLAYERS)
		exit(ft_printf("This is Corewar NOT SPARTAAAAAAAAAAA\n"));
	if (player_nbr < 0)
		exit(ft_printf("I feel sorry for your parents...\n"));
	if (player_nbr > INT_MAX)
		exit(ft_printf("GROUND-RULES BRO ! INT_MAX 2147483647 && INT_MIN -2147483648\n"));
}