/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:34:42 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/29 09:34:55 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_expand_echo(char *str, t_global *global)
{
	t_env *env;

	env = global->head_env;
	if (str[0] == '?')
		printf("%d", g_exit_status);
	else
	{
		env = find_name(&global->head_env, str, ft_strlen(str));
		printf("%s", env->var_value);
	}
}

int ft_echo(t_cmd *cmd, t_global *global)
{
	int option;
	int i;

	option = 0;
	i = 1;
	if (cmd->val[i] == NULL)
		printf(" ");
	while (cmd->val[i] != NULL)
	{
		// printf("cmd->val : %s, expand : %d\n", cmd->val[i], cmd->expand[i]);
		if (!ft_strncmp(cmd->val[i], "-n", 2))
		{
			option = 1;
			i++;
		}
		if (cmd->expand[i])
			ft_expand_echo(cmd->val[i], global);
		else if (cmd->val[i] != NULL)
			printf("%s", cmd->val[i]);
			// if (token->next->next != NULL)
			// 	printf(" ");
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
// void	ft_expand_echo(t_token *token, t_global *global)
// {
// 	t_env *env;
// 	char *name;

// 	env = global->head_env;
// 	if (token->val[1] == '?')
// 	{
// 		ft_strcpy(token->val, ft_itoa(g_exit_status));
// 		printf("%s", token->val);
// 	}
// 	else
// 	{
// 		name = edit_name(&token->val[1], '=');
// 		env = find_name(&global->head_env, name, ft_strlen(name));
// 		printf("%s",env->var_value);
// 	}

// }

// int	ft_echo(t_token *token, t_global *global)
// {
// 	int option;

// 	option = 0;
// 	while (token != NULL)
// 	{
// 		if (token->expand)
// 			ft_expand_echo(token, global);
// 		if (token->val == NULL)
// 			printf(" ");
// 		else if (!ft_strncmp(token->val, "-n", 2))
// 			option = 1;
// 		else if (token->next != NULL && !token->expand)
// 		{
// 			printf("%s",token->val);
// 			if (token->next->next != NULL)
// 				printf(" ");
// 		}
// 		token = token->next;
// 	}
// 	if (!option)
// 		printf("\n");
// 	return (0);
// }


