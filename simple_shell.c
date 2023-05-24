#include "main.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

/**
 * get_cmd - get cmd from line
 * @line: line
 * Return: cmd
 */
char *get_cmd(char *line)
{
    int len = 0;
    char *cmd;
    int i = 0;

    while (line[i] != '\0' && line[i] != ' ' && line[i] != '\n')
    {
        i++;
        len++;
    }
    cmd = (char *)malloc((len + 1) * sizeof(char));
    if (cmd == NULL)
        return (NULL);
    for (i = 0; i < len; i++)
        cmd[i] = line[i];
    cmd[len] = '\0';

    return (cmd);
}

/**
 * get_argv - split line into argv
 * @line: line
 * Return: argv
 */
#include <string.h>

char **get_argv(char *line)
{
    char **argv;
    int i = 0;
    int j = 0;
    int len = 0;
    int words = 0;

    while (line[i] != '\0')
    {
        if (line[i] == ' ')
            words++;
        i++;
    }
    words++;
    argv = (char **)malloc((words + 1) * sizeof(char *));
    if (argv == NULL)
        return (NULL);

    for (i = 0; i < words; i++)
    {
        while (line[j] != '\0' && line[j] != ' ' && line[j] != '\n')
        {
            len++;
            j++;
        }
        argv[i] = (char *)malloc((len + 1) * sizeof(char));
        if (argv[i] == NULL)
            return (NULL);

        strncpy(argv[i], &line[j - len], len);
        argv[i][len] = '\0';

        len = 0;
        while (line[j] == ' ' || line[j] == '\n')
            j++;
    }

    argv[i] = NULL;
    return argv;
}

/**
 * main - Entry point
 * @argc: arg count
 * @argv: arg vector
 * @envp: environement
 *
 * Return: status
 */
int main(int argc, char **argv, char **envp)
{
    char *line;
    char *cmd;
    int i;
    char **av;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;

    (void)argc;
    (void)argv;

    while (1)
    {
        write(STDOUT_FILENO, " ($) ", 9);
        fflush(stdout);
        read = getline(&line, &len, stdin);
        if (read != -1)
        {
            cmd = get_cmd(line);
            av = get_argv(line);
            if (access(cmd, F_OK | X_OK) == -1) {
                write(STDERR_FILENO, "Command not found\n", 18);
            } else {
                pid = fork();
                if (pid < 0)
                {
                    write(STDERR_FILENO, "Fork Failed", 11);
                    return (1);
                }
                else if (pid == 0)
                {
                    if (execve(cmd, av, envp) == -1)
                        perror("./shell");
                    _exit(0);
                }
                else
                    wait(&status);
            }
        }
        else
        {
            write(STDOUT_FILENO, "\n", 1);
            exit(0);
        }
        free(line);
        free(cmd);
        for (i = 0; av[i] != NULL; i++)
            free(av[i]);
        free(av);
    }
    return (0);
}

