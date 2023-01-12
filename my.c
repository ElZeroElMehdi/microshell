#include <stdio.h>
#include <string.h>
#include <unistd.h>
int ft_cd(char **av, int i)
{
    if (i != 2)
        write(2, "error: cd: bad arguments\n", 26);
    else if(chdir(av[1]))
        return(write(2, "error: cd\n", 11));
    return 1;
}
ft_execute(char **ar, char **env, int i);
int main(int ac , char **ar, char **env)
{
    (void)ac;
    (void)env;
    int i = 0;

    while (ar[i] && ar[++i])
    {
        ar += i; // move from programe name to first arg
        i = 0;
        while(ar[i] && strcmp(ar[i], "|") && strcmp(ar[i], ";"))
            i++;
        if(!strcmp(ar[0], "cd"))
            ft_cd(ar, i);
        else if (i)
            ft_execute(ar, env, i);
    }
}

ft_execute(char **ar, char **env, int i)
{
    int pip = 0;
    int pid;
    int fd[2];   
}