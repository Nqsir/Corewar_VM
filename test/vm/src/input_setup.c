/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_setup.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 13:45:59 by amatthys    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

static int		cor_read(char **stack, int fd, int size)
{
	if (!(*stack = ft_memalloc(size + 1)))
		return (-1);
	return (read(fd, *stack, size));
}

static int		cor_get_file(char **buff, char *filename)
{
	int		fd;
	int		read_ret;

	read_ret = 1;
	if (ft_strcmp(ft_strrchr(filename, '.'), ".cor") &&
			!cor_e("'.cor' extention required (%s)", filename))
		return (-1);
	if ((fd = open(filename, O_RDONLY)) < 0 &&
			!cor_e("Unable to open %s", filename))
		return (-1);
	read_ret = cor_read(buff, fd, CHAMP_MAX_SIZE + sizeof(t_header) + 1);
	if ((read_ret < 0) && !cor_e("Unable to read %s", filename))
		ft_memdel((void **)buff);
	close(fd);
	return (read_ret);
}

static int		cor_read_champion(t_player *player)
{
	int32_t		size;

	if ((size = cor_get_file(&player->code, player->filename)) < 0)
		return (0);
	if (size < (int)sizeof(t_header))
		return (cor_e("File too short (%s)", player->filename));
	ft_memcpy(&player->header, player->code, sizeof(t_header));
	ft_memrev(&player->header.prog_size, 4);
	if (size - sizeof(t_header) != player->header.prog_size)
		return (cor_e("%s : invalid header", player->filename));
	if (player->header.prog_size < (uint16_t)size - sizeof(t_header))
		size = player->header.prog_size;
	if (size > CHAMP_MAX_SIZE + (int)sizeof(t_header))
	{
		return (cor_e("%s too long (%i bytes / %i bytes max)", player->filename,
				player->header.prog_size, CHAMP_MAX_SIZE));
	}
	return (!size ? cor_e("%s : invalid header", player->filename) : size);
}

static int		cor_load_players(int8_t *mem, t_player **players,
		int nb_players, t_prog **progs)
{
	int		i;
	int		dist;

	dist = MEM_SIZE / nb_players;
	i = -1;
	while (players[++i])
	{
		if (!cor_add_new_prog(progs, i * dist, players[i]->id))
			return (0);
		(*progs)->did_live = 0;
		ft_memcpy(mem + (i * dist),
		players[i]->code + sizeof(t_header),
		players[i]->header.prog_size);
	}
	return (1);
}

int				cor_setup(int8_t *mem, t_player **players, int nb_players,
		t_prog **progs)
{
	int				i;

	i = -1;
	while (players[++i])
	{
		if (!cor_read_champion(players[i]))
			return (0);
		ft_memrev(&players[i]->header.magic, 4);
		if (players[i]->header.magic != COREWAR_EXEC_MAGIC)
			return (cor_e("File format unknown (%s)", players[i]->filename));
	}
	if (!cor_load_players(mem, players, nb_players, progs))
		return (0);
	cor_introduce(players);
	return (1);
}
