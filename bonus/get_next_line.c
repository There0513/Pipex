/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:04:51 by threiss           #+#    #+#             */
/*   Updated: 2021/11/04 17:09:49 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	get_next_line(char **line)
{
	char	*input;
	char	buf;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	input = malloc(sizeof(char) * 9450);
	if (!line || !input)
		return (-1);
	ret = read(0, &buf, 1);
	while (ret > 0 && buf != '\n' && buf != '\0')
	{
		input[i] = buf;
		i++;
		ret = read(0, &buf, 1);
	}
	if (i > 0)
		input[i] = '\n';
	input[++i] = '\0';
	*line = input;
	return (ret);
}
