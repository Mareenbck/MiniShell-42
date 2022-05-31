/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:08:26 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/27 15:56:15 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	ft_error(char *msg, int exit_status)
{
	printf("%s\n", msg);
	g_exit_status = exit_status;
	// return (1);
	// exit(exit_status);
}

t_token	*lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*lstlast2(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void ft_lstaddback(t_token **alst, t_token *new)
{
	t_token	*tmp;
  	if (alst)
  	{
    	if (*alst != NULL)
		{
      		tmp = *alst;
			while (tmp->next)
            	tmp = tmp->next;
        	tmp->next = new;
        	new->prev = tmp;
        	new->next = NULL;
		}
    	else
      		(*alst) = new;
  	}
}

void ft_lstaddback2(t_cmd **alst, t_cmd *new)
{
	t_cmd	*tmp;
  	if (alst)
  	{
    	if (*alst != NULL)
		{
      		tmp = *alst;
			while (tmp->next)
            	tmp = tmp->next;
        	tmp->next = new;
        	new->prev = tmp;
        	new->next = NULL;
		}
    	else
      		(*alst) = new;
  	}
}

void ft_lstaddback3(t_env **alst, t_env *new)
{
	t_env	*tmp;

  	if (alst)
  	{
    	if (*alst != NULL)
		{
      		tmp = *alst;
			while (tmp->next != NULL)
            	tmp = tmp->next;
        	tmp->next = new;
        	new->prev = tmp;
        	new->next = NULL;
		}
    	else
      		(*alst) = new;
  	}
}

void	ft_lstaddfront(t_env **alst, t_env *new)
{
	t_env *tmp;

	tmp = *alst;
	new->next = *alst;
	tmp->prev = new;
	*alst = new;
}

void	ft_lst_insert(t_env **head_env, t_env *new)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *head_env;
	if (head_env)
	{
		while ((ft_strcmp(new->var_name, tmp->var_name) > 0) && tmp->next->var_name != NULL)
			tmp = tmp->next;
		if (tmp->next->var_name != NULL && tmp->prev != NULL)
		{
			tmp2 = tmp->prev;
			tmp2->next = new;
			new->prev = tmp->prev;
			tmp->prev = new;
			new->next = tmp;
		}
		else if (tmp == *head_env)
			ft_lstaddfront(head_env, new);
		else
		{
			tmp2 = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->next = tmp2;
		}
	}
}


void ft_lst_delone(t_token *token, void (*del)(void *))
{
	if (!del || !token)
		return;
	if (token)
	{
		free(token->val);
		(*del)(token);
	}
}

void ft_lst_delone2(t_cmd *cmd, void (*del)(void *))
{
	if (!del || !cmd)
		return;
	if (cmd)
	{
		// free(cmd->val);
		free(cmd->expand);
		free(cmd->path);
		(*del)(cmd);
	}
}

void ft_lst_delone3(t_env *env, void (*del)(void *))
{
	if (!del || !env)
		return;
	if (env)
	{
		free(env->declare);
		free(env->var_name);
		free(env->var_value);
		free(env->var_sign);
		(*del)(env);
	}
}


void ft_lst_clear(t_token **head, void (*del)(void *))
{
	t_token *tmp;

	if (!del || !head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		ft_lst_delone(*head, del);
		(*head) = tmp;
	}
}

void ft_lst_clear2(t_cmd **head, void (*del)(void *))
{
	t_cmd *tmp;

	if (!del || !head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		ft_free_tab((*head)->val);
		ft_lst_delone2(*head, del);
		(*head) = tmp;
	}
}

void ft_lst_clear3(t_env **head, void (*del)(void *))
{
	t_env *tmp;

	if (!del || !head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		ft_lst_delone3(*head, del);
		(*head) = tmp;
	}
}

char *ft_strdup_bis(const char *s1, int len)
{
	char *str;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (--len >= 0)
		str[len] = s1[len];
	return (str);
}

int	ft_wrong(char *str)
{
	printf("%s\n", str);
	return(1);
}
