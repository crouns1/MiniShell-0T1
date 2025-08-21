/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:48:30 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 15:37:26 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void update_env_var(t_env *node, char *kv)
{
    ft_free(node->s);
    node->s = kv;
}

static void add_env_var(t_env **env, char *kv)
{
    t_env *node = ft_malloc(sizeof(t_env));
    t_env *last;

    node->s = kv;
    node->next = NULL;

    if (!*env)
        *env = node;
    else
    {
        last = *env;
        while (last->next)
            last = last->next;
        last->next = node;
    }
}

void set_env(t_env **env, char *key, char *value)
{
    t_env *node;
    char  *kv;
    char  *tmp;

    if (value)
    {
        tmp = ft_strjoin(ft_strdup(key), "=");
        kv = ft_strjoin(tmp, value);
    }
    else
    {
        kv = ft_strdup(key);
    }

    node = find_env(*env, key);
    if (node)
        update_env_var(node, kv);
    else
        add_env_var(env, kv);
}

void unset_env(t_env **env, char *key)
{
    t_env *cur = *env;
    t_env *prev = NULL;
    size_t len = ft_strlen(key);

    while (cur)
    {
        if (!ft_strncmp(cur->s, key, len) && (cur->s[len] == '=' || cur->s[len] == '\0'))
        {
            if (prev)
                prev->next = cur->next;
            else
                *env = cur->next;
            ft_free(cur->s);
            ft_free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
