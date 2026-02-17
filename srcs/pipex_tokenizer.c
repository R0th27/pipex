/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoe <htoe@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:58:45 by htoe              #+#    #+#             */
/*   Updated: 2026/02/17 18:14:24 by htoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_parse_case	count_token(char *str, t_token *token)
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

static int	token_counter(char *str, t_parse_case *state)
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

static char	*build_cmd_argv(char *s, int *i, t_parse_case *state)
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

char	**cmd_tokenizer(char *cmd_str, t_error *err)
{
	char			**argv;
	t_parse_case	state;
	t_token			token;

	token.count = token_counter(cmd_str, &state);
	if (state != PARSE_OK)
		return (*err = ERR_OK, NULL);
	argv = (char **)malloc(sizeof(char *) * (token.count + 1));
	if (!argv)
		return (*err = ERR_MALLOC, NULL);
	token.index = 0;
	token.i = 0;
	while (token.index < token.count)
	{
		argv[token.index++] = build_cmd_argv(cmd_str, &token.i, &state);
		if (state != PARSE_OK)
			return (free_array(&argv), *err = ERR_MALLOC, NULL);
	}
	argv[token.index] = NULL;
	return (*err = ERR_OK, argv);
}
