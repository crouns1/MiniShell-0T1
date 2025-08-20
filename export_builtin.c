#include "minishell.h"

// Helper to print error for invalid identifier
static void export_error(const char *arg)
{
    write(2, "export: '", 9);
    write(2, arg, ft_strlen(arg));
    write(2, "': not a valid identifier\n", 26);
}

// Export builtin implementation
int ft_export(t_env **env, char **argv)
{
    int i = 1;
    if (!argv[1])
    {
        print_sorted_env(*env);
        return 0;
    }
    while (argv[i])
    {
        char *arg = argv[i];
        if (ft_strnstr(arg, "+=", ft_strlen(arg)))
        {
            export_error(arg);
        }
        else
        {
            char *eq = ft_strchr(arg, '=');
            int keylen = eq ? (eq - arg) : ft_strlen(arg);
            char key[1024];
            ft_strlcpy(key, arg, keylen + 1);
            if (!is_valid_identifier(key))
            {
                export_error(arg);
            }
            else if (eq)
            {
                set_env(env, key, eq + 1);
            }
            else
            {
                // Mark as exported, create if not present
                if (!find_env(*env, key))
                    set_env(env, key, NULL);
            }
        }
        i++;
    }
    return 0;
}