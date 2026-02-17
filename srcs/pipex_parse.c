/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:44:50 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 16:14:56 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	env_init(int argc, char **argv, char **envp, t_env *env)
{
	env->argc = argc;
	env->argv = argv;
	env->envp = envp;
}

int	pipeline_init(t_env env, t_pipeline **pl)
{
	*pl = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!(*pl))
		return (0);
	(*pl)->io_type = detect_input_type(env.argv[1]);
	(*pl)->cmd_counts = env.argc - 3 - ((*pl)->io_type == INPUT_HEREDOC);
	(*pl)->cmds = ft_calloc((*pl)->cmd_counts, sizeof(t_cmd));
	if (!(*pl)->cmds)
		return (free(*pl), 0);
	(*pl)->infile = -1;
	(*pl)->outfile = -1;
	return (1);
}

int	parse_pipeline(t_env env, t_pipeline *pl)
{
	int	start;

	start = 1 + (pl->io_type == INPUT_HEREDOC);
	pl->infile = setup_input_fd(pl->io_type, env.argv[start]);
	if (pl->infile < 0)
	{
		if (pl->io_type == INPUT_HEREDOC)
			error_perror("heredoc");
		else
			error_perror(env.argv[1]);
	}
	pl->outfile = setup_output_fd(pl->io_type, env.argv[env.argc - 1]);
	if (pl->outfile < 0)
		return (error_perror(env.argv[env.argc - 1]), 0);
	return (0);
}
