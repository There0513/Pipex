/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:27:26 by threiss           #+#    #+#             */
/*   Updated: 2021/11/07 14:25:44 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
 **	INPUT
 **	close fds you don't use
 **	duplicate file descriptors		-> dup2(int oldfd, int newfd)
 **	close old 'output'
 */
void	child_proc_one(int *fds, char **av, char **envp, int fd_in)
{
	close(fds[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		exit(1);
	close(fd_in);
	close(fds[1]);
	exec_prep(av[2], envp, 0);
}

/*
 **	OUTPUT
 **	close fds you don't use
 **	duplicate file descriptors		-> dup2(int oldfd, int newfd)
 **	close old 'output'
 */
void	child_proc_two(int *fds, char **av, char **envp, int fd_out)
{
	close(fds[1]);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		exit(1);
	close(fd_out);
	close(fds[0]);
	exec_prep(av[3], envp, 0);
}

/*
 **	pipe(fds) -> create pipe
 **	fork()	  -> create child process
 */
void	pipex(int fd_in, int fd_out, char **av, char **envp)
{
	int		fds[2];
	pid_t	pid;
	pid_t	pid2;

	if (pipe(fds) == -1)
	{
		perror("pipe()");
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("fork()");
	if (pid == 0)
		child_proc_one(fds, av, envp, fd_in);
	pid2 = fork();
	if (pid2 == -1)
		perror("fork()");
	if (pid2 == 0)
		child_proc_two(fds, av, envp, fd_out);
	waitpid(-1, NULL, 0);
}
