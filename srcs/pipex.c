/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:37 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 19:08:04 by htoe             ###   ########.fr       */
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
	t_env		env;

	usage_check(argc, argv);
	env_init(argc, argv, envp, &env);
	if (!pipeline_init(env, &pl))
		return (1);
	if (!setup_io(env, pl))
		return (pipeline_destroy(&pl), 1);
	if (!pipeline_fill(env, pl))
		return (pipeline_destroy(&pl), 1);
	status = pipeline_exec(&pl, env);
	pipeline_display(pl);
	pipeline_destroy(&pl);
	return (status);
}
