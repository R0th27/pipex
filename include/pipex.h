/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:57:33 by htoe              #+#    #+#             */
/*   Updated: 2026/02/18 13:23:04 by htoe             ###   ########.fr       */
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

//init + parse
void		env_init(int argc, char **argv, char **envp, t_env *env);
int			pipeline_init(t_env env, t_pipeline **pl);
void		setup_io(t_env env, t_pipeline *pl);

//cmd + token
int			pipeline_fill(t_env env, t_pipeline *pl);
char		**cmd_tokenizer(char *cmd_str, t_error *err);

//paths
char		**extract_path_dirs(char **envp);
char		**build_paths(char *cmd, char **dirs, t_error *err);

//exec
int			pipeline_exec(t_pipeline **pl);
int			exec_cmd(t_cmd cmd, char **envp);

//error
void		error_usage(int bonus);
void		error_print(const char *target, const char *message);
void		error_perror(const char *target);
void		error_cmd_not_found(const char *cmd);
int			error_code_from_errno(int err);

//io
int			setup_input_fd(t_in_type type, const char *arg);
int			setup_output_fd(t_in_type type, const char *arg);

//fd
int			safe_dup(t_exec *exec, t_pipeline *pl);
int			safe_pipe(t_exec *exec, int last);
void		fd_closure(t_exec *exec, t_pipeline *pl, int pipe_in);

//utils
t_in_type	detect_input_type(const char *arg);
int			heredoc_read(int fd, const char *limiter);

//free_up
void		pipeline_destroy(t_pipeline **pl);
void		cmd_destroy(t_cmd *cmd);
void		free_array(char ***arr);

#endif
