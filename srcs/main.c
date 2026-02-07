/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:47:05 by htoe              #+#    #+#             */
/*   Updated: 2026/02/08 04:12:09 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	pipex(int argc, char **argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (argc < 5)
		error_exit(ERR_USAGE, NULL);
	cmd = ft_split(argv[1], ' ');
	path = resolve_path(cmd[0], envp);
	if (path)
		printf("%s\n", path);
	free_split(cmd);
	free(path);
	(void)argv;
	(void)envp;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	status;

	status = pipex(argc, argv, envp);
	return (status);
}
