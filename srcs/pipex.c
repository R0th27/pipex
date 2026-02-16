/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:37 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 00:19:30 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmds;
	int		i;
	t_parse_error	err;

	if (argc < 2)
		return (1);
	cmds = parse_command((argv + 1)[0], &err);
	if (!cmds)
		return (1);
	i = 0;
	while (cmds[i])
		printf("%s\n", cmds[i++]);
	(void)cmds;
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
