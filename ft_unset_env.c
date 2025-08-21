#include "minishell.h"


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
    t_env *node = find_env(env, key);
    char *eq;

    if (!node)
        return NULL;
    eq = ft_strchr(node->s, '=');
    if (!eq)
        return NULL;
    return eq + 1;
}

// Compare two env strings lexicographically
static int cmp_env_str(const char *sa, const char *sb)
{
    size_t la = ft_strlen((char *)sa);
    size_t lb = ft_strlen((char *)sb);
    size_t minl = la < lb ? la : lb;
    int r = ft_strncmp((char *)sa, (char *)sb, (int)minl + 1);
    if (r != 0)
        return r;
    if (la == lb)
        return 0;
    return la < lb ? -1 : 1;
}

// swap two pointers
static void swap_ptrs(char **a, char **b)
{
    char *t = *a;
    *a = *b;
    *b = t;
}

// simple bubble sort for char * array
static void bubble_sort_env(char **arr, int count)
{
    int i, j;
    int swapped;
    if (!arr || count < 2)
        return;
    for (i = 0; i < count - 1; i++)
    {
        swapped = 0;
        for (j = 0; j < count - 1 - i; j++)
        {
            if (cmp_env_str(arr[j], arr[j + 1]) > 0)
            {
                swap_ptrs(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

// count nodes in env list
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

// build array of pointers to env->s (no strdup)
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

// print one env entry in export format
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

// Print env in bash export format, sorted (bubble sort)
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
            *env = node;
        else
        {
            last = *env;
            while (last->next)
                last = last->next;
            last->next = node;
        }
    }
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