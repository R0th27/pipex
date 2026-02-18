/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:37 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 13:23:15 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	usage_check(int argc, char **argv)
{
	if (argc < 5 || (detect_input_type(argv[1]) == INPUT_HEREDOC && argc < 6))
		return (error_usage(1), 0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipeline	*pl;
	int			status;
	t_env		env;

	if (!usage_check(argc, argv))
		return (1);
	env_init(argc, argv, envp, &env);
	if (!pipeline_init(env, &pl))
		return (1);
	if (!pipeline_fill(env, pl))
		return (pipeline_destroy(&pl), 1);
	status = pipeline_exec(&pl);
	pipeline_destroy(&pl);
	return (status);
}
