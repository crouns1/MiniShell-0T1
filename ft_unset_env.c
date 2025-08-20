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

// Check if a string is a valid environment variable identifier
// int is_valid_identifier(const char *s)
// {
//     if (!s || (!ft_isalpha(*s) && *s != '_'))
//         return 0;
//     for (int i = 1; s[i] && s[i] != '='; i++)
//         if (!ft_isalnum(s[i]) && s[i] != '_')
//             return 0;
//     return 1;
// }

// Compare function for qsort
static int cmp_env(const void *a, const void *b)
{
    char *sa = *(char **)a;
    char *sb = *(char **)b;
    return ft_strncmp(sa, sb, ft_strlen(sa) > ft_strlen(sb) ? ft_strlen(sa) : ft_strlen(sb));
}

// Print env in bash export format, sorted
void print_sorted_env(t_env *env)
{
    int count = 0;
    t_env *tmp = env;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    char **arr = ft_malloc(sizeof(char *) * count);
    tmp = env;
    for (int i = 0; i < count; i++)
    {
        arr[i] = tmp->s;
        tmp = tmp->next;
    }
    qsort(arr, count, sizeof(char *), cmp_env);
    for (int i = 0; i < count; i++)
    {
        char *eq = ft_strchr(arr[i], '=');
        if (eq)
        {
            int keylen = eq - arr[i];
            write(1, "declare -x ", 11);
            write(1, arr[i], keylen);
            write(1, "=\"", 2);
            write(1, eq + 1, ft_strlen(eq + 1));
            write(1, "\"\n", 2);
        }
        else
        {
            write(1, "declare -x ", 11);
            write(1, arr[i], ft_strlen(arr[i]));
            write(1, "\n", 1);
        }
    }
    ft_free(arr);
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
        kv = ft_strdup(key); 
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
