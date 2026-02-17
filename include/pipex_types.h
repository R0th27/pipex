/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:22 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 19:09:33 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_TYPES_H
# define PIPEX_TYPES_H

typedef enum e_parse_case
{
	PARSE_OK,
	PARSE_UNCLOSED_QUOTE,
	PARSE_BACKSLASH,
	PARSE_MALLOC_FAIL
}	t_parse_case;

typedef enum e_error
{
	ERR_OK,
	ERR_MALLOC
}	t_error;

typedef enum e_in_type
{
	INPUT_FILE,
	INPUT_HEREDOC
}	t_in_type;

typedef struct s_token
{
	int	in_sq;
	int	in_word;
	int	count;
	int	i;
	int	index;
}	t_token;

typedef struct s_exec
{
	int		saved_errno;
	int		status;
	pid_t	last_pid;
	pid_t	pid;
}	t_exec;

typedef struct s_cmd
{
	char	**argv;
	char	**paths;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd		*cmds;
	int			cmd_counts;
	t_in_type	io_type;
	int			infile;
	int			outfile;
}	t_pipeline;

typedef struct s_env
{
	int		argc;
	char	**argv;
	char	**envp;	
}	t_env;

#endif
