#include "minishell.h"

t_env *find_env(t_env *env, char *key)
{
    size_t len = ft_strlen(key);
    while (env)
    {
        if (!ft_strncmp(env->s, key, len) && env->s[len] == '=')
            return env;
        env = env->next;
    }
    return NULL;
}

char *get_env_value(t_env *env, char *key)
{
    t_env *node = find_env(env, key);
    if (!node)
        return NULL;
    return node->s + ft_strlen(key) + 1;
}

void set_env(t_env **env, char *key, char *value)
{
    t_env *node;
    t_env *last;
    char  *kv;
    char  *tmp;

    if (value)
    {
        tmp = ft_strjoin(ft_strdup(key), "=");
        kv = ft_strjoin(tmp, value);
    }
    else
    {
        kv = ft_strjoin(ft_strdup(key), "=");
    }

    node = find_env(*env, key);
    if (node)
    {
        ft_free(node->s);
        node->s = kv;
    }
    else
    {
        node = ft_malloc(sizeof(t_env));
        node->s = kv;
        node->next = NULL;

        if (!*env)
            *env = node; // list empty
        else
        {
            last = *env;
            while (last->next)
                last = last->next;
            last->next = node; // append at end
        }
    }
}


// void set_env(t_env **env, char *key, char *value)
// {
//     t_env *node;
//     char  *kv;
//     char  *tmp;

//     if (value)
//     {
//         tmp = ft_strjoin(ft_strdup(key), "=");
//         kv = ft_strjoin(tmp, value);
//     }
//     else
//     {
//         kv = ft_strjoin(ft_strdup(key), "=");
//     }

//     node = find_env(*env, key);
//     if (node)
//     {
//         ft_free(node->s);
//         node->s = kv;
//     }
//     else
//     {
//         node = ft_malloc(sizeof(t_env));
//         node->s = kv;
//         node->next = *env;
//         *env = node;
//     }
// }

void unset_env(t_env **env, char *key)
{
    t_env *cur = *env, *prev = NULL;
    size_t len = ft_strlen(key);

    while (cur)
    {
        if (!ft_strncmp(cur->s, key, len) && cur->s[len] == '=')
        {
            if (prev) prev->next = cur->next;
            else *env = cur->next;
            ft_free(cur->s);
            ft_free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
char **env_to_array(t_env *env)
{
    int     count = 0;
    t_env   *tmp = env;
    char    **arr;

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
