/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:18:49 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/04 11:19:02 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_global *global)
{
	t_env *tmp;

	tmp = global->head_env;
	while (tmp->next != NULL)
	{
		if (*tmp->var_value == '\0' && *tmp->var_sign == '\0')
			printf("%s %s%s\n", tmp->declare, tmp->var_name, tmp->var_sign);
		else
			printf("%s %s%s\"%s\"\n", tmp->declare, tmp->var_name, tmp->var_sign, tmp->var_value);
		tmp = tmp->next;
	}
}

void	ft_change_env(char *name, char *value, t_global *global)
{
	char **env;
	int i;
	char *tmp;

	i = 0;
	env = global->env;
	tmp = ft_strjoin(name, "=");
	while(env[i])
	{
		if (!ft_strncmp(env[i], tmp, ft_strlen(tmp)))
		{
			free(env[i]);
			env[i] = ft_strjoin(tmp, value);
			break ;
		}
		i++;
	}
}

// void	ft_concat_env(char *name, char *value, t_global *global)
// {
// 	char **env;
// 	int i;
// 	char *tmp = NULL;

// 	i = 0;
// 	env = global->env;
// 	printf("NAME : %s, VALUE : %s\n", name, value);
// 	while(env[i])
// 	{
// 		if (!ft_strncmp(env[i], name, ft_strlen(name)))
// 		{
// 			tmp = ft_strdup(env[i]);
// 			free(env[i]);
// 			env[i] = ft_strjoin(tmp, value);
// 			break ;
// 		}
// 		i++;
// 	}
// }

bool ft_str_isalnum(char *str)
{
	int i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}

//FAIRE UEN STRUCT TMP POUR ENREGISTRER NOM ET SIGNE FORMATE
int	ft_export(t_cmd *cmd, t_global *global)
{
	t_env *env;
	t_env *new_env;
	char *value;
	char *sign;
	char *name;
	int i = 1;

	env = NULL;
	if (cmd->val[i] == NULL)
		ft_print_export(global);
	// VERSION ANTERIEUR VERIFICATION DU TOKEN SI WORD
	while (cmd->val[i] != NULL)
	{
		value = check_value(cmd->val[i]);
		if (!check_name(cmd->val[i]))
		{
			sign = init_sign(cmd->val[i]);
			name = edit_name(cmd->val[i], '=');
			if (!ft_str_isalnum(name))
				ft_error("Syntax Error", ERROR);
			env = find_name(&global->head_env, name, (ft_strlen(name) + 1));
			if (env)
			{
				if (sign[0] == '+')
				{
					env->var_value = ft_strjoin(env->var_value, value);
					ft_change_env(name, env->var_value, global);
				}
				else
				{
					free(env->var_sign);
					env->var_sign = init_sign(cmd->val[i]);;
					free(env->var_value);
					env->var_value = check_value(cmd->val[i]);
					ft_change_env(name, env->var_value, global);
				}
			}
			else
			{
				ft_insert_tab(global->env, cmd->val[i]);
				new_env = create_var_env(name, cmd->val[i]);
				ft_lst_insert(&global->head_env, new_env);
			}
		}
		i++;;
		free(sign);
		free(value);
	}
	// ft_print_env(head_env);
	return (0);
}
