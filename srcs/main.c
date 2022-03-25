/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:37:48 by threiss           #+#    #+#             */
/*   Updated: 2021/11/05 14:39:19 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **av, char **envp)
{
	int	fd_in;
	int	fd_out;

	if (ac != 5)
		return (1);
	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_in < 0)
	{
		perror(av[1]);
		exit(1);
	}
	if (fd_out < 0)
	{
		perror(av[4]);
		exit(1);
	}
	pipex(fd_in, fd_out, av, envp);
	return (0);
}
