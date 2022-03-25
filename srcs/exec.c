/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:16:48 by threiss           #+#    #+#             */
/*   Updated: 2021/11/09 12:08:23 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
		return (0);
	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i++] = s2[j];
	ptr[i] = '\0';
	return (ptr);
}

/*
**	Exit code 127 means job's command can not be found or executed.
*/
void	exec_path(char **paths, char **split, char **envp, int i)
{
	char	*path_tmp;
	char	*new_path;

	while (paths[++i])
	{
		path_tmp = ft_strjoin(paths[i], "/");
		if (path_tmp == 0)
			return ;
		new_path = ft_strjoin(path_tmp, split[0]);
		if (new_path == 0)
			return ;
		if (access(new_path, F_OK) == 0)
			execve(new_path, split, envp);
		free(path_tmp);
		free(new_path);
	}
	ft_putstr_fd(split[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	freeeeee(paths, split);
	exit(127);
}

int	check_vars(char **split, char **envp)
{
	if (split == 0)
		return (-1);
	if (split[0] == 0)
	{
		ft_putstr_fd("command not found\n", 2);
		free(split);
		return (-1);
	}
	if (envp[0] == NULL)
	{
		ft_putstr_fd(split[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (-1);
	}
	return (1);
}

void	double_check_env(char **envp, char **split, int i)
{
	if (!envp[i] || ft_strncmp(envp[i], "PATH", 4) != 0)
	{
		ft_putstr_fd(split[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

/*
 **	find PATH in env + check if paths/cmd exists
 */
void	exec_prep(char *str, char **envp, int i)
{
	char	**split;
	char	**paths;

	split = ft_split(str, ' ');
	if (check_vars(split, envp) == -1)
		return ;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	double_check_env(envp, split, i);
	paths = ft_split(envp[i], ':');
	if (paths == 0)
		return ;
	if (split[0][0] == '/')
	{
		if (access(split[0], F_OK) == 0)
			execve(split[0], split, envp);
		else
		{
			perror(split[0]);
			freeeeee(paths, split);
			exit (127);
			return ;
		}
	}
	exec_path(paths, split, envp, -1);
}
