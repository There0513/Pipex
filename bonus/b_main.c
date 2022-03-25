/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:06:51 by threiss           #+#    #+#             */
/*   Updated: 2021/11/07 14:19:45 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	check_fds(t_args *args, char **av, int ac)
{
	if (args->fd_in != 500)
	{
		if (args->fd_in < 0)
		{
			perror(av[1]);
		}
	}
	if (args->fd_out < 0)
	{
		perror(av[ac - 1]);
		exit(1);
	}
	return (1);
}

int	prep(t_args *args, char **av, int ac, int *fds)
{
	pid_t	pid;

	args->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	args->fd_in = 500;
	check_fds(args, av, ac);
	args->i = 3;
	if (pipe(fds) == -1)
	{
		perror("pipe()");
		return (-2);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		return (-2);
	}
	return (pid);
}

void	gnl_next(char **line, char **av, int *fds)
{
	if (ft_strncmp(*line, av[2], ft_strlen(av[2])) == 0
		&& ft_strlen(av[2]) == (ft_strlen(*line) - 1))
	{
		free(*line);
		exit(0);
	}
	write(fds[1], *line, ft_strlen(*line));
	free(*line);
}

void	here_doc(t_args *args, char **av, int ac)
{
	int		fds[2];
	pid_t	pid;
	char	*line;

	pid = prep(args, av, ac, fds);
	if (pid == -2)
		return ;
	else if (pid == 0)
	{
		close(fds[0]);
		while (get_next_line(&line) == 1)
			gnl_next(&line, av, fds);
	}
	else
	{
		close(fds[1]);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			exit(1);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_args	args;

	if (ac < 5)
		return (0);
	args.envp = envp;
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac >= 6)
		here_doc(&args, av, ac);
	else if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6)
	{
		ft_putstr_fd("Not enough arguments for here_doc.\n", 2);
		ft_putstr_fd("./pipex here_doc LIMITER <cmd> <cmd1> <...> outfile\n", 2);
		return (0);
	}
	else
	{
		args.fd_in = open(av[1], O_RDONLY);
		args.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		check_fds(&args, av, ac);
		if (dup2(args.fd_in, STDIN_FILENO) == -1)
			exit(1);
		args.i = 2;
	}
	pipex_bonus(av, ac, args);
	return (0);
}
