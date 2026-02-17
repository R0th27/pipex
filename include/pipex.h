/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:57:33 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 13:56:22 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "pipex_types.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>

//parse
char		**cmd_tokenizer(char *cmd_str);

//error
void		error_usage(void);
void		error_print(const char *target, const char *message);
void		error_perror(const char *target);
int			error_code_from_errno(int err);
void		error_cmd_not_found(const char *cmd);

//utils
t_in_type	detect_input_type(const char *arg);
int			heredoc_read(int fd, const char *limiter);

//free_up
void		pipeline_destroy(t_pipeline **pl);
void		cmd_destroy(t_cmd *cmd);
void		free_array(char ***arr);

#endif
