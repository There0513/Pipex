/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:50:22 by threiss           #+#    #+#             */
/*   Updated: 2021/11/09 12:05:10 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (0);
	if (start >= ft_strlen(s))
		return (ptr);
	while (s[start] && i < len)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}

static int	ft_get_words(char const *s, char c)
{
	int		i;
	int		words;

	i = 1;
	if (s[0] != c)
		words = 1;
	else
		words = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i - 1] == c && s[i])
		{
			words++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (words);
}

void	two_more_lines(int *i, char const *s, char c, int *len)
{
	while (s[*i] != c && s[*i])
	{
		(*len)++;
		(*i)++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i_res;
	int		i;
	int		len;

	i_res = -1;
	i = 0;
	if (!s)
		return (NULL);
	res = malloc((ft_get_words(s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return (0);
	while (s[i] && ft_get_words(s, c) > 0)
	{
		len = 0;
		while (s[i] == c)
			i++;
		two_more_lines(&i, s, c, &len);
		if (len > 0)
			res[++i_res] = ft_substr(s, i - len, len);
	}
	res[++i_res] = 0;
	return (res);
}
