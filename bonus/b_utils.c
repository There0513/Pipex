/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:27:26 by threiss           #+#    #+#             */
/*   Updated: 2021/11/07 14:24:51 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
 **	INPUT
 **	close fds you don't use
 **	duplicate file descriptors		-> dup2(int oldfd, int newfd)
 **	close old 'output'
 */
void	b_child_proc(char *av, char **envp)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
	{
		perror("pipe()");
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("fork()");
	else if (pid == 0)
	{
		close(fds[0]);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(1);
		exec_prep(av, envp, 0);
	}
	else
	{
		close(fds[1]);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			exit(1);
		waitpid(pid, NULL, 0);
	}
}

/*
 **	pipe(fds) -> create pipe
 **	fork()	  -> create child process
 ** execute last cmd at the end
 */
void	pipex_bonus(char **av, int ac, t_args args)
{
	int	i;

	i = args.i;
	while (i < ac - 2)
	{
		b_child_proc(av[i], args.envp);
		i++;
	}
	if (dup2(args.fd_out, STDOUT_FILENO) == -1)
		exit(1);
	exec_prep(av[ac - 2], args.envp, 0);
}
