/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:38:57 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/21 11:51:30 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_env_nodes(t_env *env)
{
    int c = 0;
    while (env)
    {
        c++;
        env = env->next;
    }
    return c;
}

static char **build_env_array(t_env *env, int count)
{
    char **arr;
    int i = 0;
    t_env *tmp = env;

    if (count <= 0)
        return NULL;
    arr = ft_malloc(sizeof(char *) * count);
    while (tmp && i < count)
    {
        arr[i++] = tmp->s;
        tmp = tmp->next;
    }
    return arr;
}

static void print_env_entry(const char *s)
{
    char *eq = ft_strchr((char *)s, '=');
    if (eq)
    {
        int keylen = eq - s;
        write(1, "declare -x ", 11);
        write(1, s, keylen);
        write(1, "=\"", 2);
        write(1, eq + 1, ft_strlen(eq + 1));
        write(1, "\"\n", 2);
    }
    else
    {
        write(1, "declare -x ", 11);
        write(1, s, ft_strlen((char *)s));
        write(1, "\n", 1);
    }
}

void print_sorted_env(t_env *env)
{
    int count = count_env_nodes(env);
    char **arr;
    int i;

    if (count == 0)
        return;
    arr = build_env_array(env, count);
    if (!arr)
        return;
    bubble_sort_env(arr, count);
    for (i = 0; i < count; i++)
        print_env_entry(arr[i]);
    ft_free(arr);
}

char **env_to_array(t_env *env)
{
    int count = 0;
    t_env *tmp = env;
    char **arr;

    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    arr = ft_malloc(sizeof(char *) * (count + 1));
    count = 0;
    tmp = env;
    while (tmp)
    {
        arr[count++] = ft_strdup(tmp->s);
        tmp = tmp->next;
    }
    arr[count] = NULL;
    return arr;
}
