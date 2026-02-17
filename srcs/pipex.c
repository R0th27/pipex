/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:37 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 13:54:06 by htoe             ###   ########.fr       */
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

static void	env_init(int argc, char **argv, char **envp, t_env *env)
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

int	main(int argc, char **argv, char **envp)
{
	t_pipeline	*pl;
	int			status;
	t_env		env;

	usage_check(argc, argv);
	env_init(argc, argv, envp, &env);
	if (!pipeline_init(env, &pl))
		return (1);
	if (!parse_pipeline(env, pl))
		return (1);
	status = 0;
	return (status);
}
