#include "main.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

char *get_cmd(char *line)
{
	int len = 0;
	char *cmd;
	int i = 0;

	while(line[i] != '\0' && line[i] != ' ' && line[i] != '\n')
	{
		i++;
		len++;
	}
	cmd = (char *) malloc(len * sizeof(char));
	if (cmd == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		cmd[i] = line[i];

	return (cmd);
}

char **get_argv(char *line)
{
	int nt = 0;
	int i = 0;
	int j = 0;
	int len = 0;
	char **av;

	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			nt++;
		i++;
	}
	nt++;
	av =  (char **) malloc(sizeof(char *) * nt);
	if (av == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		len 


	}

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
	char **av;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;

	(void) argc;
	(void) av;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		fflush(stdout);
		read = getline(&line, &len, stdin);
		if (read != -1)
		{
			cmd = get_cmd(line);
			pid = fork();
			if (pid < 0)
			{
				write(STDERR_FILENO, "Fork Failed", 11);
				return (1);
			}
			else if (pid == 0)
			{
				if (execve(cmd, argv, envp) == -1)
					perror("./shell");
				_exit(0);
			}
			else
				wait(&status);
		}
		else
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}
	}
	free(line);
	free(cmd);
	return (0);
}
