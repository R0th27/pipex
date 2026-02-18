/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:37 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 13:28:16 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	usage_check(int argc)
{
	if (argc != 5)
		return (error_usage(0), 0);
	return (1);
}

static int	mandatory_pipeline_init(t_env env, t_pipeline **pl)
{
	*pl = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!(*pl))
		return (0);
	(*pl)->io_type = INPUT_FILE;
	(*pl)->cmd_counts = 2;
	(*pl)->cmds = ft_calloc((*pl)->cmd_counts, sizeof(t_cmd));
	if (!(*pl)->cmds)
		return (free(*pl), 0);
	(*pl)->infile = -1;
	(*pl)->outfile = -1;
	(*pl)->envp = env.envp;
	setup_io(env, *pl);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipeline	*pl;
	int			status;
	t_env		env;

	if (!usage_check(argc))
		return (1);
	env_init(argc, argv, envp, &env);
	if (!mandatory_pipeline_init(env, &pl))
		return (1);
	if (!pipeline_fill(env, pl))
		return (pipeline_destroy(&pl), 1);
	status = pipeline_exec(&pl);
	pipeline_destroy(&pl);
	return (status);
}
