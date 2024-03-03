/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:34:59 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/31 12:21:29 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_word(char const *str, char delimiter);
static int		word_len(char const *str, char delimiter);
static void		free_mem(char **mem, int i);
static void		skip_delimiter(char const **ps, char const **str, char delim);

char	**ft_split(char const *s, char c)
{
	int			i;
	int			num_words;
	int			len;
	char		**mem;

	i = -1;
	num_words = count_word(s, c);
	mem = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!mem)
		return (mem);
	while (++i < num_words)
	{
		skip_delimiter(&s, NULL, c);
		len = word_len(s, c);
		mem[i] = malloc(len + 1);
		if (!mem[i])
		{
			free_mem(mem, i);
			return (0);
		}
		ft_strlcpy(*(mem + i), s, len + 1);
		s += len;
	}
	mem[i] = NULL;
	return (mem);
}

static void	skip_delimiter(char const **ps, char const **str, char delim)
{
	if (str == NULL)
	{
		while (**ps == delim || **ps == 0)
			(*ps)++;
	}
	else
	{
		while (**str == delim)
			(*str)++;
	}
}

static int	word_len(char const *str, char delimiter)
{
	int	cnt;

	cnt = 0;
	skip_delimiter(NULL, &str, delimiter);
	while (*str && *str++ != delimiter)
		cnt++;
	return (cnt);
}

static int	count_word(char const *str, char delimiter)
{
	int	cnt;

	cnt = 0;
	if (str == NULL)
		return (cnt);
	while (*str && *str == delimiter)
		str++;
	while (*str)
	{
		while ((*str && *str != delimiter))
			str++;
		cnt++;
		if (*str == 0)
			break ;
		while (*str == delimiter)
			str++;
	}
	return (cnt);
}

static void	free_mem(char **mem, int i)
{
	int		j;
	char	**new_mem;

	j = 0;
	new_mem = mem;
	while (j < i)
		free(new_mem[j++]);
	free(new_mem);
}
