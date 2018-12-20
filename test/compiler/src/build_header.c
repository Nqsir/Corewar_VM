/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_header.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 18:13:49 by nerahmou    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int	asm_check_max_size(char *data_type)
{
	if (!ft_strcmp(data_type, NAME_CMD_STRING))
		return (PROG_NAME_LENGTH);
	return (COMMENT_LENGTH);
}

static int	asm_jump_n_check_chars(char *str, int i, t_asm *prog)
{
	int	tmp;

	tmp = i;
	while (str[i] && str[i] != '"')
		i++;
	if (!str[i])
		return (asm_e(prog, "Expecting ending \'\"\'"));
	if (i != tmp || ft_strncmp(str, NAME_CMD_STRING,
				ft_strlen(NAME_CMD_STRING)))
		return (i);
	return (asm_e(prog, "Empty value not allowed", str[i]));
}

static int	check_player_info(char *line, char *data, int *ise, t_asm *p)
{
	char		**tab;

	if (!(tab = ft_strsplit(line, COMMENT_CHAR)))
		return (asm_e(p, MALLOC_FAILED));
	ise[0] += jump_spaces(tab[0], ise[0]);
	if ((ise[1] = ise[0] + 1) && tab[0][ise[0]++] != '"' && ft_free_grid(&tab))
		return (asm_e(p, "%s: Expecting surrounding \'\"\'", data + 1));
	if (!(ise[0] = asm_jump_n_check_chars(tab[0], ise[0], p))
			&& ft_free_grid(&tab))
		return (0);
	ise[2] = ise[0]++;
	ise[0] += jump_spaces(tab[0], ise[0]);
	if (tab[0][ise[0]] && ft_free_grid(&tab))
		return (asm_e(p, "%s: Expecting '\\n' after", data + 1));
	if (ise[2] - ise[1] >= asm_check_max_size(data) && ft_free_grid(&tab))
		return (asm_e(p, "%s too long", data + 1));
	return (ft_free_grid(&tab));
}

static	int	get_player_info(char *data, t_asm *p, char *dest)
{
	char		*line;
	int			ise[3];

	while (p->file[p->line])
	{
		line = p->file[p->line] + jump_spaces(p->file[p->line], 0);
		if (ft_strlen(line) && line[0] != COMMENT_CHAR)
		{
			ise[0] = ft_strlen(data);
			if (ft_strncmp(line, data, ise[0]) || !jump_spaces(line, ise[0]))
				return (asm_e(p, "Line : '%s' not found", data));
			if (!check_player_info(line, data, (int *)ise, p))
				return (0);
			ft_strncpy(dest, line + ise[1], ise[2] - ise[1]);
			p->line++;
			return (1);
		}
		p->line++;
	}
	return (p->line-- && asm_e(p, "Line : '%s' not found", data));
}

int			asm_build_header(t_asm *prog)
{
	if (!get_player_info(NAME_CMD_STRING, prog, prog->header->prog_name)
		|| !get_player_info(COMMENT_CMD_STRING, prog, prog->header->comment))
		return (0);
	prog->header->magic = COREWAR_EXEC_MAGIC;
	asm_memrev((unsigned char *)&prog->header->magic, sizeof(uint32_t));
	return (1);
}
