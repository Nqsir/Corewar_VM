/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kevazoul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 19:43:46 by kevazoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/17 19:43:54 by kevazoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_iter(char *str, void *ft_check_f(int c))
{
	int i;

	i = -1;
	while (str[++i])
		if (!(ft_check_f(str[i])))
			return (0);
	return (1);
}
