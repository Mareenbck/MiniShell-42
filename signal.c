/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:30:28 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/19 12:15:25 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void siginthandler()
{
	ft_putstr_fd("", 1);
}

void signalslash()
{
	ft_putstr_fd("", 1);
}



char		*ft_get_pwd(void)
{
	int		i;
	char	*buf;

	i = 5;
	if (!(buf = malloc(i)))
		return (0);
	while (!getcwd(buf, i))
	{
		if (errno != ERANGE)
			return (0);
		i += 5;
		free(buf);
		buf = malloc(i);
	}
	return (buf);
}

void	handle_sigint(int sig)
{

	if (sig == SIGINT || sig == SIGQUIT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();

	}
}
void		ft_signal(int i)
{
	if (i == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 1)
	{
		signal(SIGINT, SIG_DFL);
	}
	else if (i == 2)
	{
		signal(SIGINT, handle_sigint);
	}
}

