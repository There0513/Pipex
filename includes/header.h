/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:36:19 by threiss           #+#    #+#             */
/*   Updated: 2021/11/07 19:58:02 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <error.h>

typedef struct s_args
{
	int		fd_in;
	int		fd_out;
	char	**envp;
	int		i;
}				t_args;

char	**ft_split(char const *str, char c);
int		check_vars(char **split, char **envp);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *str, int fd);
void	freeeeee(char **paths, char **split);
void	pipex(int fd_in, int fd_out, char **av, char **envp);
void	pipex_bonus(char **av, int ac, t_args args);
void	exec_prep(char *str, char **envp, int i);
int		get_next_line(char **line);

#endif
