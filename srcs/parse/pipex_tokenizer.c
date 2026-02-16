/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:58:45 by htoe              #+#    #+#             */
/*   Updated: 2026/02/16 18:20:32 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_parse_case	count_token(char *str, t_token *token)
{
	while (str[++token->i])
	{
		if (!token->in_sq && str[token->i] == ' ')
			token->in_word = 0;
		else
		{
			if (!token->in_word)
			{
				token->count++;
				token->in_word = 1;
			}
			if (str[token->i] == '\'')
				token->in_sq = !token->in_sq;
			else if (str[token->i] == '\\' && !token->in_sq)
			{
				if (!str[token->i + 1])
					return (PARSE_BACKSLASH);
				token->i++;
			}
		}
	}
	if (token->in_sq)
		return (PARSE_UNCLOSED_QUOTE);
	return (PARSE_OK);
}

int	token_counter(char *str, t_parse_case *state)
{
	t_token			token;

	token.in_sq = 0;
	token.in_word = 0;
	token.count = 0;
	token.i = -1;
	*state = count_token(str, &token);
	if (*state != PARSE_OK)
		return (0);
	return (token.count);
}

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

char	*build_cmd_argv(char *s, int *i, t_parse_case *state)
{
	char	*buffer;
	t_token	token;

	while (s[*i] == ' ')
		(*i)++;
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(s) - *i + 1));
	if (!buffer)
		return (*state = PARSE_MALLOC_FAIL, NULL);
	token.i = 0;
	token.in_sq = 0;
	while (s[*i] && (token.in_sq || s[*i] != ' '))
	{
		if (s[*i] == '\'')
			token.in_sq = !token.in_sq;
		else if (s[*i] == '\\' && !token.in_sq)
		{
			(*i)++;
			buffer[token.i++] = s[*i];
		}
		else
			buffer[token.i++] = s[*i];
		(*i)++;
	}
	buffer[token.i] = '\0';
	return (buffer);
}

char	**cmd_tokenizer(char *cmd_str)
{
	char			**argv;
	int				token_count;
	t_parse_case	state;
	int				i;
	int				index;

	token_count = token_counter(cmd_str, &state);
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
	return (argv);
}
