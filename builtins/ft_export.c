
#include "builtins.h"
#include <ctype.h>
#include <string.h>

extern char	**environ;

static int	valid(char *s)
{
	int	i;

	if (!s || (!isalpha((unsigned char)s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!isalnum((unsigned char)s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char **a, char ***e)
{
	int	i = 1, st;

	i = 1, st = 0;
	char *eq, *name;
	if (!a[1])
		return (ft_env(a, *e));
	while (a[i])
	{
		if (!valid(a[i]))
			(write(2, "minishell: export: `", 20), write(2, a[i], strlen(a[i])),
				write(2, "': not a valid identifier\n", 26), st = 1);
		else if ((eq = strchr(a[i], '=')))
			(name = ft_substr(a[i], eq - a[i]), setenv(name, eq + 1, 1),
				ft_free(name));
		else
			setenv(a[i], "", 1);
		i++;
	}
	*e = environ;
	static_info()->env = arr_list(*e);
	return (st);
}

// typedef struct s_env
// {
//     char            *key;
//     char            *value;
//     int             exported;
//     struct s_env    *next;
// }   t_env;

// /* ---------------- utils ---------------- */
// static int ft_isalpha_(int c) { return (isalpha((unsigned char)c)); }
// static int ft_isalnum_(int c) { return (isalnum((unsigned char)c)); }

// static char *ft_strdup_(const char *s)
// {
//     size_t len = strlen(s);
//     char *dup = malloc(len + 1);
//     if (!dup)
//         return (NULL);
//     memcpy(dup, s, len);
//     dup[len] = '\0';
//     return (dup);
// }

// static char *ft_substr_(const char *s, int start, int len)
// {
//     char *sub;
//     if (start < 0 || len < 0 || (size_t)start > strlen(s))
//         return (ft_strdup_(""));
//     if ((size_t)(start + len) > strlen(s))
//         len = strlen(s) - start;
//     sub = malloc(len + 1);
//     if (!sub)
//         return (NULL);
//     memcpy(sub, s + start, len);
//     sub[len] = '\0';
//     return (sub);
// }

// /* ---------------- env helpers ---------------- */
// static int valid_identifier(const char *s)
// {
//     int i = 0;
//     if (!s)
//         return (0);
//     if (!ft_isalpha_(*s) && *s != '_')
//         return (0);
//     i = 1;
//     while (s[i] && s[i] != '=')
//     {
//         if (!ft_isalnum_(s[i]) && s[i] != '_')
//             return (0);
//         i++;
//     }
//     return (1);
// }

// static t_env *find_env(t_env *env, const char *key)
// {
//     while (env)
//     {
//         if (strcmp(env->key, key) == 0)
//             return (env);
//         env = env->next;
//     }
//     return (NULL);
// }

// static void add_or_update_env(t_env **env, char *key, char *value, int exported)
// {
//     t_env *node = find_env(*env, key);
//     if (node)
//     {
//         if (node->value)
//             free(node->value);
//         if (value)
//             node->value = ft_strdup_(value);
//         else
//             node->value = NULL;
//         node->exported = 1;
//     }
//     else
//     {
//         node = malloc(sizeof(t_env));
//         if (!node)
//             return ;
//         node->key = ft_strdup_(key);
//         if (value)
//             node->value = ft_strdup_(value);
//         else
//             node->value = NULL;
//         node->exported = exported;
//         node->next = *env;
//         *env = node;
//     }
// }

// static void print_export(t_env *env)
// {
//     while (env)
//     {
//         if (env->exported)
//         {
//             if (env->value)
//             {
//                 write(1, "declare -x ", 11);
//                 write(1, env->key, strlen(env->key));
//                 write(1, "=\"", 2);
//                 write(1, env->value, strlen(env->value));
//                 write(1, "\"\n", 2);
//             }
//             else
//             {
//                 write(1, "declare -x ", 11);
//                 write(1, env->key, strlen(env->key));
//                 write(1, "\n", 1);
//             }
//         }
//         env = env->next;
//     }
// }

// /* ---------------- builtin export ---------------- */
// int ft_export(char **args, t_env **env)
// {
//     int i = 1;
//     int status = 0;

//     if (!args[1])
//     {
//         print_export(*env);
//         return (0);
//     }
//     while (args[i])
//     {
//         char *eq = strchr(args[i], '=');
//         char *key;
//         char *value;

//         value = NULL;
//         if (eq)
//         {
//             key = ft_substr_(args[i], 0, eq - args[i]);
//             value = eq + 1;
//         }
//         else
//             key = ft_strdup_(args[i]);
//         if (!valid_identifier(key))
//         {
//             write(2, "minishell: export: `", 20);
//             write(2, args[i], strlen(args[i]));
//             write(2, "': not a valid identifier\n", 27);
//             status = 1;
//             free(key);
//             i++;
//             continue;
//         }
//         add_or_update_env(env, key, value, 1);
//         free(key);
//         i++;
//     }
//     return (status);
// }