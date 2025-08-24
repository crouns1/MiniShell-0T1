/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_help2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:44:37 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/24 21:27:12 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *find_env(t_env *env, char *key)
{
    size_t len = ft_strlen(key);
    while (env)
    {
        if ((!ft_strncmp(env->s, key, len) && env->s[len] == '=' ) || env
        ->s[len] == '\0')
            return env;
        env = env->next;
    }
    return NULL;
}

char *get_env_value(t_env *env, char *key)
{
    int key_len = ft_strlen(key);

    while (env)
    {
        if (ft_strncmp(env->s, key, key_len) == 0 && env->s[key_len] == '=')
        {
            return (env->s + key_len + 1); 
        }
        env = env->next;
    }
    return NULL;
}
// char *get_env_value(t_env *env, char *key)
// {
//     t_env *node = find_env(env, key);
//     char *eq;

//     if (!node)
//         return NULL;
//     eq = ft_strchr(node->s, '=');
//     if (!eq)
//         return NULL;
//     return eq + 1;
// }

int cmp_env_str(const char *sa, const char *sb)
{
    size_t la = ft_strlen((char *)sa);
    size_t lb = ft_strlen((char *)sb);
    size_t minl;
    int r;

    if (la < lb)
        minl = la;
    else
        minl = lb;

    r = ft_strncmp((char *)sa, (char *)sb, (int)minl + 1);
    if (r != 0)
        return r;
    if (la == lb)
        return 0;
    if (la < lb)
        return -1;
    else
        return 1;
}
void swap_ptrs(char **a, char **b)
{
    char *t = *a;
    *a = *b;
    *b = t;
}

void bubble_sort_env(char **arr, int count)
{
    int i = 0, j, swapped;
    if (!arr || count < 2)
        return;
    while (i < count - 1)
    {
        swapped = 0;
        j = 0;
        while (j < count - 1 - i)
        {
            if (cmp_env_str(arr[j], arr[j + 1]) > 0)
            {
                swap_ptrs(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
            j++;
        }
        if (!swapped)
            break;
        i++;
    }
}
