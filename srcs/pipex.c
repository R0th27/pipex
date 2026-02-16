/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:37 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 18:37:35 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	usage_check(int argc, char **argv)
{
	if (argc < 5 || (detect_input_type(argv[1]) == INPUT_HEREDOC && argc < 6))
	{
		error_usage();
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipeline	*pl;
	int			status;
	char		**cmd;

	usage_check(argc, argv);
	cmd = cmd_tokenizer(argv[1]);
	int	i = 0;
	while (cmd[i])
		printf("%s\n", cmd[i++]);
	(void)envp;
	(void)pl;
	(void)status;
	return (0);
}
