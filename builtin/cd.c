/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:25:51 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/27 09:26:01 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_token *token, t_global *global)
{
	char *new;
	t_env *oldpwd;
	t_env *newpwd;
	t_env *home;

	if (token->next && token->next->val != NULL)
		printf("cd : too many arguments\n");
	oldpwd = find_name(&global->head_env, "OLDPWD=");
	if (oldpwd != NULL)
		oldpwd->var_value = getcwd(NULL, 0);
	printf("oldpwd name : %s, value %s\n", oldpwd->var_name, oldpwd->var_value);
	if (token->val == NULL || !ft_strncmp(token->val, "~", 1))
	{
		// DOIT RETOURNER A HOME OU RACINE DU MINISHELL ??
		home = find_name(&global->head_env, "HOME=");
		chdir(home->var_value);
	}
	else
	{
		new = ft_strjoin(getcwd(NULL,0), "/");
		new = ft_strjoin(new, token->val);
		chdir(new);
	}
	newpwd = find_name(&global->head_env, "PATH=");
	if (newpwd != NULL)
		newpwd->var_value = getcwd(NULL, 0);
	printf("new path %s\n", newpwd->var_value);
	return (0);
}
