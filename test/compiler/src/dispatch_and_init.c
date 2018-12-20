/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dispatch_and_init.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 15:36:58 by nerahmou    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		asm_set_filenames(t_asm *prog, char *filename)
{
	char	*tmp;

	if (!(prog->s_file = ft_strdup(filename)))
		return (ft_error(MALLOC_FAILED, 0));
	tmp = ft_strrchr(filename, '.');
	if (!tmp || ft_strcmp(tmp, ".s"))
		return (ft_error("Error: \".s\" extension required\n", 0));
	*tmp = 0;
	filename = ft_strrchr(filename, '/') ?
		ft_strrchr(filename, '/') + 1 : filename;
	if (!(prog->filename = ft_strcatdup(filename, ".cor")))
		return (ft_error(MALLOC_FAILED, 0));
	return (1);
}

static int		asm_init(t_session *session)
{
	int		i;

	i = -1;
	if (!(session->asms = ft_memalloc(
		sizeof(void *) * (session->files_count + 1))))
		return (ft_error(MALLOC_FAILED, 0));
	while (++i < session->files_count)
	{
		if (!(session->asms[i] = ft_memalloc(sizeof(t_asm))))
			return (ft_error(MALLOC_FAILED, 0));
		if (!(session->asms[i]->header = ft_memalloc(sizeof(t_header))))
			return (ft_error(MALLOC_FAILED, 0));
		if (!(session->asms[i]->file = ft_get_file(session->filenames[i])))
			return (ft_error("Error: Unable to open file\n", 0));
		if (!(asm_set_filenames(session->asms[i], session->filenames[i])))
			return (0);
		session->asms[i]->res_size = sizeof(t_header);
		if (!(session->asms[i]->res = ft_memalloc(sizeof(t_header))))
			return (ft_error(MALLOC_FAILED, 0));
	}
	return (1);
}

int				asm_dispatch(t_session *s)
{
	int		i;

	i = -1;
	if (!asm_init(s))
		return (s->success = 0);
	while (s->success && ++i < s->files_count)
		if (!asm_build_header(s->asms[i]) || !asm_process(s->asms[i]))
			return (s->success = 0);
	return (1);
}
