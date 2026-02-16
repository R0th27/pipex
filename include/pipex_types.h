/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:58:22 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 00:18:32 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_TYPES_H
# define PIPEX_TYPES_H

typedef enum e_parse_error
{
	PARSE_OK,
	PARSE_UNCLOSED_QUOTE,
	PARSE_MALLOC_FAIL
}	t_parse_error;

typedef enum e_input_type
{
	INPUT_FILE,
	INPUT_HEREDOC
}	t_input_type;

typedef struct s_cmd
{
	char	**argv;
	char	**paths;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd			*cmds;
	int				cmd_counts;
	t_input_type	io_type;
	int				infile;
	int				outfile;
}	t_pipeline;

#endif
