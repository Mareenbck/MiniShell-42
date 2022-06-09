/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:18:49 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/09 13:18:31 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_global *global)
{
	t_env	*tmp;

	tmp = global->head_env;
	while (tmp->next != NULL)
	{
		if (*tmp->var_value == '\0' && *tmp->var_sign == '\0')
			printf("%s %s%s\n", tmp->declare, tmp->var_name, tmp->var_sign);
		else
			printf("%s %s%s\"%s\"\n", tmp->declare,
				tmp->var_name, tmp->var_sign, tmp->var_value);
		tmp = tmp->next;
	}
}

int	ft_change_env(char *name, char *value, t_global *global)
{
	char	**env;
	int		i;
	char	*tmp;

	i = 0;
	env = global->env;
	tmp = ft_strjoin(name, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], tmp, ft_strlen(tmp)))
		{
			free(env[i]);
			env[i] = ft_strjoin(tmp, value);
			return (0);
		}
		i++;
	}
	tmp = ft_strjoin(tmp, value);
	ft_insert_tab(global->env, tmp);
	free(tmp);
	return (1);
}

void	ft_insert_new_env(char *cmd, t_global *global, char *name, char *sign)
{
	t_env	*new_env;
	char	*tmp;

	if (ft_strchr(cmd, '=') && !ft_strchr(cmd, '+'))
		ft_insert_tab(global->env, cmd);
	if (sign[0] == '+')
	{
		tmp = ft_strtrim(sign, "+");
		new_env = create_var_env(name, cmd, tmp);
		free(tmp);
	}
	else
		new_env = create_var_env(name, cmd, sign);
	ft_lst_insert(&global->head_env, new_env);
	free(name);
}

void	ft_change_export(t_global *global, char *name, char *sign, char *cmd)
{
	t_env	*env;
	char	*value;

	env = find_name(&global->head_env, name, (ft_strlen(name) + 1));
	if (env)
	{
		if (sign[0] == '+')
		{
			value = check_value(cmd);
			env->var_value = ft_strjoin(env->var_value, value);
			free(value);
			ft_change_env(name, env->var_value, global);
		}
		else
		{
			free(env->var_sign);
			env->var_sign = init_sign(cmd);
			free(env->var_value);
			env->var_value = check_value(cmd);
			ft_change_env(name, env->var_value, global);
		}
	}
	else
		ft_insert_new_env(cmd, global, name, sign);
	free(sign);
}

int	ft_export(t_cmd *cmd, t_global *global)
{
	char	*sign;
	char	*name;
	int		i;

	i = 1;
	if (cmd->val[i] == NULL)
		ft_print_export(global);
	while (cmd->val[i] != NULL)
	{
		if (!check_name(cmd->val[i]))
		{
			sign = init_sign(cmd->val[i]);
			name = edit_name(cmd->val[i], '=');
			if (!name || !ft_str_isalnum(name))
			{
				free(sign);
				printf("not a valid identifier\n");
				return (1);
			}
			ft_change_export(global, name, sign, cmd->val[i]);
		}
		i++;
	}
	return (0);
}
