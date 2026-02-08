/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:47:05 by htoe              #+#    #+#             */
/*   Updated: 2026/02/08 08:20:21 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	create_child(t_cmd *cmd, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		exec_cmd(cmd, envp);
	else
	{
		waitpid(pid, &status, 0);
		printf("status: %d\n", status >> 8);
	}
}

void	file_test(int ac, char **av)
{
	t_input_type	type;
	int				infile;
	int				outfile;

	type = INPUT_HEREDOC;
	infile = setup_input_fd(type, av[1]);
	outfile = setup_output_fd(type, av[ac - 1]);
	printf("infile %d\n", infile);
	printf("outfile %d\n", outfile);
}

int	pipex(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;

	if (argc < 5)
		return (error_return(ERR_USAGE, NULL));
	cmd = cmd_create(argv[1], envp);
	if (!cmd)
		return (1);
	create_child(cmd, envp);
	cmd_destroy(cmd);
	file_test(argc, argv);
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
