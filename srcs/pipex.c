/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:37 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 17:43:15 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmds;
	int		i;

	if (argc < 2)
		return (1);
	cmds = cmd_tokenizer(argv[1]);
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
