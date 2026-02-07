/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:47:05 by htoe              #+#    #+#             */
/*   Updated: 2026/02/08 05:00:20 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	pipex(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		i;

	if (argc < 5)
		error_exit(ERR_USAGE, NULL);
	cmd = cmd_create(argv[1], envp);
	i = 0;
	while (cmd -> cmd_argv[i])
		printf("%s\n", cmd -> cmd_argv[i++]);
	if (cmd -> path)
		printf("%s\n", cmd -> path);
	printf("%d\n", cmd -> in_fd);
	printf("%d\n", cmd -> out_fd);
	cmd_destroy(cmd);
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
