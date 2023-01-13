#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

int tmp;

int ft_error(char *msg)
{
    int i = 0;
    while(msg[i])
        write(2, &msg[i++], 1);
    return (1);
}

int ft_cd(char **ar, int i)
{
    if (i != 2)
        return (ft_error("bad args\n"));
    if (chdir(ar[1]))
        return (ft_error("error: cd: cannot change directory to ") && ft_error(ar[1]) && ft_error("\n"));
    return 0;
}

int ft_execute(char **ar, char **env, int i)
{
    int pid;
    int pip = 0;
    int fd[2];
    if (ar[i] && !strcmp(ar[i], "|"))
        pip = 1;
    if (pip && pipe(fd) == -1)
        return (ft_error("fatal\n"));
    pid = fork();
    if (!pid)
    {
        ar[i] = 0;
        if (dup2(tmp, 0) == -1 || close(tmp) == -1)
            return (ft_error("error: fatal"));
        if (pip && (dup2(fd[1], 1) == -1  || close (fd[1]) == -1 || close(fd[0]) == -1))
            return (ft_error("error: fatal"));
        execve(ar[0], ar, env);
        return ft_error("not f");
    }
    if (pip && (dup2(fd[0], tmp)==-1 || close(fd[1]) == -1 || close(fd[0]) == -1))
        return (ft_error("error fatal"));
    if (!pip && (dup2(0, tmp) == -1 || waitpid(pid, NULL, 0) == -1))
        return ft_error("no");
    return 1;
}

int main (int ac, char **ar, char **env)
{
    int i = 0;
    tmp = dup(0);
    (void)ac;
    while (ar[i] && ar[++i])
    {
        ar++;
        i = 0;
        while (ar[i] && strcmp(ar[i], "|") && strcmp(ar[i], ";"))
            i++;
        if (!strcmp(ar[0], "cd"))
            ft_cd(ar, i);
        else if (i)
            ft_execute(ar, env, i);
    }
}