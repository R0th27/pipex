/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:20:49 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 16:03:38 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char ***arr)
{
	int	i;

	if (!*arr)
		return ;
	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

void	quote_copy(char *to, char *from, int *start, int *i)
{
	(*i)++;
	while (from[*i])
	{
		if (from[*i] == '\'' && (!from[*i + 1] || from[*i + 1] == ' '))
			break;
		if (from[*i] == '\'')
			(*i)++;
		if (from[*i] != '\'')
			to[(*start)++] = from[(*i)++];
	}
	(*i)++;
	to[*start] = '\0';
}

void	normal_copy(char *to, char *from, int *start, int *i)
{
	while (from[*i])
	{
		if (from[*i] == ' ')
			break;
		else if (from[*i] == '\'')
			quote_copy(to, from, start, i);
		else if (from[*i] == '\\')
		{
			(*i)++;
			to[(*start)++] = from[*i];
		}
		else
			to[(*start)++] = from[*i];
		(*i)++;
	}
	to[*start] = '\0';
}

char	*build_cmd_argv(char *s, int *i, t_parse_case *state)
{
	char	*str;
	char	*ret;
	int		len;
	int		start;

	len = ft_strlen(s) - *i;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (*state = PARSE_MALLOC_FAIL, NULL);
	if (s[*i] == ' ')
	{
		space_skip(s, i);
		(*i)++;				
	}
	start = 0;
	if (s[*i] == '\'')
		quote_copy(str, s, &start, i);
	else
		normal_copy(str, s, &start, i);
	printf("%s\n", str);
	ret = ft_strdup(str);
	free(str);
	*state = PARSE_OK;
	return (ret);
}

char	**cmd_argv_retrieve(char *cmd_str)
{
	char			**argv;
	int				token_count;
	t_parse_case	state;
	int				i;
	int				index;

	state = PARSE_OK;
	token_count = count_token(cmd_str, &state);
	printf("token: %d\n", token_count);
	if (state != PARSE_OK)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (!argv)
		return (NULL);
	index = 0;
	i = 0;
	while (i < token_count)
	{
		argv[i++] = build_cmd_argv(cmd_str, &index, &state);
		if (state != PARSE_OK)
			return (free_array(&argv), NULL);
	}
	argv[i] = NULL;
	free_array(&argv);
	return (argv);
}
