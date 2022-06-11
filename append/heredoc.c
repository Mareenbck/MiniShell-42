/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:43:07 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/10 13:05:25 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*expand_heredoc(char *str, t_env *env, t_global *global, int heredoc)
{
	if (start_with_dollar(str))
	{
		env = find_name(&global->head_env, &str[1], ft_strlen(&str[1]) - 1);
		if (env)
		{
			write(heredoc, env->var_value, ft_strlen(env->var_value));
			write(heredoc, "\n", 1);
		}
	}
	else
		write(heredoc, str, ft_strlen(str));
	return (env);
}

char	*init_heredoc(char *str)
{
	write(1, ">", 1);
	ft_signal(3);
	str = readline(STDIN_FILENO);
	ft_signal(0);
	str = ft_strjoin(str, "\n");
	return (str);
}

int	check_error(int heredoc)
{
	if (heredoc == -1)
	{
		perror("Command not found");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	launch_heredoc(char *lim, int heredoc, t_global *global)
{
	t_env	*env;
	char	*str = NULL;

	while (1)
	{
		str = init_heredoc(str);
		if (!ft_strncmp(lim, str, ft_strlen(lim)))
			break ;
		if (g_exit_status == 130)
		{
			break ;
			return (close(heredoc), g_exit_status = 130, -1);
		}
		env = expand_heredoc(str, env, global, heredoc);
		free(str);
	}
	free(str);
	close(heredoc);
	return (0);
}

int	ft_heredoc(char *lim, t_global *global)
{
	int		heredoc;
	void	*ctl;

	ctl = rl_getc_function;
	rl_getc_function = getc;
	g_exit_status = 0;
	if (check_lim(lim) != 0)
		return (EXIT_FAILURE);
	heredoc = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_error(heredoc);
	launch_heredoc(lim, heredoc, global);
	rl_getc_function = ctl;
	return (heredoc);
}
