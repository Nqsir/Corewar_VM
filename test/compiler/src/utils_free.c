/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_free.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:44:03 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 15:32:17 by nerahmou    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void			asm_free_asm(t_asm **prog)
{
	if ((*prog)->file)
		ft_free_grid((char ***)&(*prog)->file);
	if ((*prog)->res)
		free((*prog)->res);
	if ((*prog)->error)
		free((*prog)->error);
	if ((*prog)->header)
		free((*prog)->header);
	if ((*prog)->filename)
		free((*prog)->filename);
	if ((*prog)->s_file)
		free((*prog)->s_file);
	if ((*prog)->instruc)
		(*prog)->instruc = clear_instruction_lst((*prog)->instruc);
	if ((*prog)->labels)
		(*prog)->labels = clear_labels((*prog)->labels);
	if ((*prog)->labels_to_rep)
		(*prog)->labels_to_rep = clear_labels_to_rep((*prog)->labels_to_rep);
	if ((*prog)->to_append)
		(*prog)->to_append = clear_to_append((*prog)->to_append);
	ft_memdel((void **)prog);
}

void			asm_free_asm_array(t_asm ***asms)
{
	int		i;

	i = -1;
	if (asms)
		while (asms[++i] && (*asms)[i])
			asm_free_asm(&(*asms)[i]);
	ft_memdel((void **)asms);
}

void			asm_free(t_session *session)
{
	asm_free_asm_array(&session->asms);
}
