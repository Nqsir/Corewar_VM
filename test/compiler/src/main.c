/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 15:37:36 by nerahmou    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>

static	int	asm_write(t_asm *prog)
{
	int	fd;

	prog->header->prog_size = prog->prog_size;
	asm_memrev(&prog->header->prog_size, 4);
	ft_memcpy(prog->res, (const char *)prog->header, sizeof(t_header));
	if (!(fd = open(prog->filename, O_CREAT | O_WRONLY | O_TRUNC, 0666)))
		return (asm_e(prog, "unable to create %s", prog->filename));
	write(fd, prog->res, prog->res_size);
	close(fd);
	return (1);
}

static	int	asm_save(t_asm **asms)
{
	while (*asms)
		if (!asm_write(*(asms++)))
			return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_session	session;

	if (argc < 2)
		return (ft_error("usage: ./asm files\n", 1));
	else if (argc > MAX_PLAYERS + 1)
		return (ft_error("too much arguments\n", 1));
	else
	{
		session.success = 1;
		session.filenames = &argv[1];
		session.files_count = argc - 1;
		asm_dispatch(&session);
	}
	if (session.success)
		ft_putstr_fd("Success!\n", 2);
	if (session.success)
		session.success = asm_save(session.asms);
	asm_free(&session);
	return (!session.success);
}
