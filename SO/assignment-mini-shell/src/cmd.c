// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>

#include "cmd.h"
#include "utils.h"

#define READ		0
#define WRITE		1
#define PERM		0644

/**
 * Internal change-directory command.
 */
static bool shell_cd(word_t *dir)
{
	char *nextDir, *prevDir, *home = getenv("HOME"), *path, cwd[1024];

	if (dir) {
		nextDir = get_word(dir);
	} else {
		l_check(!home, "home not found or is not set.", "home", 0, "error", true);
		nextDir = home;
	}

	l_check(!nextDir, "the directory doesn't exist or there is no access to it", "nextDir", 0, "error", true);

	if (!strcmp(nextDir, "-")) {
		prevDir = getenv("OLDPWD");
		l_check(!prevDir, "can't use - because there is no previous directory", "prevDir", 0, "error", true);
		nextDir = prevDir;
	}

	path = getcwd(cwd, sizeof(cwd));

	l_check(!path, "returned value is NULL", "getcwd()", 1, "warning", -8);

	if (path)
		l_check(setenv("OLDPWD", cwd, 1) == -1, "returned value is -1", "setenv()", 1, "error", -8);

	l_check(chdir(nextDir) == -1, "returned value is -1", "chdir()", 1, "error", true);
	return false;
}

/**
 * Internal exit/quit command.
 */
static int shell_exit(void)
{
	exit(0);
	return SHELL_EXIT;
}

/**
 * Parse a simple command (internal, environment variable assignment,
 * external command).
 */
static int parse_simple(simple_command_t *s, int level, command_t *father)
{
	pid_t pid;
	char **argv;
	int flag, fd, size, status;
	const char *next_cmd, *command;

	l_check(!s, "null command", "s", 0, "error", -1);

	command = s->verb->string;

	// exit / quit command
	if (!strcmp(command, "quit") || !strcmp(command, "exit"))
		return shell_exit();

	// cd command
	if (!strcmp(command, "cd")) {
		if (s->out) {
			flag = O_WRONLY | O_CREAT | (s->io_flags == 1 ? O_APPEND : O_TRUNC);
			fd = open(get_word(s->out), flag, PERM);

			l_check(fd == -1, "file couldn't be opened", "fd", 0, "error", -1);
			l_check(close(fd) == -1, "file couldn't be closed", "fd", 1, "error", -1);
		}

		return shell_cd(s->params);
	}

	if (s->verb->next_part) {
		if (!strcmp(s->verb->next_part->string, "=")) {
			next_cmd = get_word(s->verb->next_part->next_part);

			l_check(!command || !next_cmd, "at least one of them is NULL", "command / next_cmd", 0, "error", -1);
			l_check(setenv(command, next_cmd, 1) == -1, "returned value is -1", "setenv()", 1, "error", -1);

			return 0;
		}

		l_check(1, "Not a environment variable assignment", "undefined", 0, "error", -1);
	}

	// external commands
	pid = fork();

	l_check(pid == -1, "fork() didn't work", "pid", 0, "error", -1);

	if (!pid) {	// redirect
		if (s->in) {	//input
			flag = O_RDONLY;
			fd = open(get_word(s->in), flag);

			l_check(fd == -1, "didn't work", "open()", 1, "error", -1);
			l_check(dup2(fd, STDIN_FILENO) == -1, "didn't work", "dup2()", 1, "error", -1);
			l_check(close(fd) == -1, "didn't work", "close()", 1, "error", -1);
		}

		// output and error
		if (s->out && s->err && !strcmp(get_word(s->out), get_word(s->err))) {
			flag = O_WRONLY | O_CREAT | O_TRUNC;
			fd = open(get_word(s->out), flag, PERM);

			l_check(fd == -1, "didn't work", "open()", 1, "error", -1);
			l_check(dup2(fd, STDOUT_FILENO) == -1, "didn't work", "dup2()", 1, "error", -1);
			l_check(dup2(fd, STDERR_FILENO) == -1, "didn't work", "dup2()", 1, "error", -1);
			l_check(close(fd) == -1, "didn't work", "close()", 1, "error", -1);

		} else { // output
			if (s->out) {
				flag = O_WRONLY | O_CREAT | (s->io_flags == 1 ? O_APPEND : O_TRUNC);
				fd = open(get_word(s->out), flag, PERM);

				l_check(fd == -1, "didn't work", "open()", 1, "error", -1);
				l_check(dup2(fd, STDOUT_FILENO) == -1, "didn't work", "dup2()", 1, "error", -1);
				l_check(close(fd) == -1, "didn't work", "close()", 1, "error", -1);
			}

			if (s->err) { // error
				flag = O_WRONLY | O_CREAT | (s->io_flags == 2 ? O_APPEND : O_TRUNC);
				fd = open(get_word(s->err), flag, PERM);

				l_check(fd == -1, "didn't work", "open()", 1, "error", -1);
				l_check(dup2(fd, STDERR_FILENO) == -1, "didn't work", "dup2()", 1, "error", -1);
				l_check(close(fd) == -1, "didn't work", "close()", 1, "error", -1);
			}
		}

		argv = get_argv(s, &size);
		l_check(!argv, "didn't work", "get_argv()", 1, "error", -1);

		if (execvp(argv[0], argv) == -1) {
			printf("Execution failed for '%s'\n", argv[0]);
			exit(-1);
		}
	}

	// for parent process wait for child
	l_check(waitpid(pid, &status, 0) == -1, "child process didn't die", "waitpid()", 1, "error", -1);

	return status;
}

/**
 * Process two commands in parallel, by creating two children.
 */
static bool run_in_parallel(command_t *cmd1, command_t *cmd2, int level, command_t *father)
{
	pid_t pid_1, pid_2;
	int status, result;

	pid_1 = fork();
	l_check(pid_1 == -1, "fork() didn't work", "pid_1", 0, "error", true);

	if (!pid_1) { // child
		result = parse_command(cmd1, level + 1, father);
		l_check(result == -1, "can't parse and execute", "parse_command()", 1, "error", true);
		exit(result);
	}

	pid_2 = fork();
	l_check(pid_2 == -1, "fork() didn't work", "pid_2", 0, "error", true);

	if (!pid_2) { // child
		result = parse_command(cmd2, level + 1, father);
		l_check(result == -1, "can't parse and execute", "parse_command()", 1, "error", true);
		exit(result);
	}

	// for parents process wait for children
	l_check(waitpid(pid_1, &status, 0) == -1, "child process didn't die", "waitpid()", 1, "error", true);
	l_check(waitpid(pid_2, &status, 0) == -1, "child process didn't die", "waitpid()", 1, "error", true);

	return status;
}

/**
 * Run commands by creating an anonymous pipe (cmd1 | cmd2).
 */
static bool run_on_pipe(command_t *cmd1, command_t *cmd2, int level, command_t *father)
{
	pid_t pid_1, pid_2;
	int pipes_cmd[2], result, status;

	l_check(pipe(pipes_cmd) == -1, "can't create pipe", "pipe()", 1, "error", true);

	pid_1 = fork();
	l_check(pid_1 == -1, "fork() didn't work", "pid_1", 0, "error", true);

	if (!pid_1) {	// child process
		l_check(close(pipes_cmd[READ]) == -1, "can't close the read of pipe", "close()", 1, "error", true);
		l_check(dup2(pipes_cmd[WRITE], STDOUT_FILENO) == -1, "can't redirect stdout", "dup2()", 1, "error", true);

		result = parse_command(cmd1, level, father);
		l_check(result == -1, "can't parse and execute", "parse_command()", 1, "error", true);
		exit(result);
	}

	pid_2 = fork();
	l_check(pid_2 == -1, "fork() didn't work", "pid_2", 0, "error", true);

	if (!pid_2) {	// child process
		l_check(close(pipes_cmd[WRITE]) == -1, "can't close the write of pipe", "close()", 1, "error", true);
		l_check(dup2(pipes_cmd[READ], STDIN_FILENO) == -1, "can't redirect stdin", "dup2()", 1, "error", true);

		result = parse_command(cmd2, level, father);
		l_check(result == -1, "can't parse and execute", "parse_command()", 1, "error", true);
		exit(result);
	}

	// for parents
	l_check(close(pipes_cmd[READ]) == -1, "can't close the read of pipe", "close()", 1, "error", true);
	l_check(close(pipes_cmd[WRITE]) == -1, "can't close the write of pipe", "close()", 1, "error", true);

	// for parents process wait for children
	l_check(waitpid(pid_1, &status, 0) == -1, "child process didn't die", "waitpid()", 1, "error", true);
	l_check(waitpid(pid_2, &status, 0) == -1, "child process didn't die", "waitpid()", 1, "error", true);

	return status;
}

/**
 * Parse and execute a command.
 */
int parse_command(command_t *c, int level, command_t *father)
{
	int result;

	l_check(!c, "command is NULL", "c", 0, "error", -1);

	if (c->op == OP_NONE)
		return parse_simple(c->scmd, level, father);

	switch (c->op) {
	case OP_SEQUENTIAL:
		l_try(parse_command(c->cmd1, level, father) == -1);
		l_try((result = parse_command(c->cmd2, level, father)) == -1);
		break;

	case OP_PARALLEL:
		l_try((result = run_in_parallel(c->cmd1, c->cmd2, level, father)) == true);
		break;

	case OP_CONDITIONAL_ZERO:
		result = parse_command(c->cmd1, level, father);
		l_try(result == -1);

		if (!result)
			l_try((result = parse_command(c->cmd2, level, father)) == -1);
		break;

	case OP_CONDITIONAL_NZERO:
		result = parse_command(c->cmd1, level, father);
		l_try(result == -1);

		if (result)
			l_try((result = parse_command(c->cmd2, level, father)) == -1);
		break;

	case OP_PIPE:
		l_try((result = run_on_pipe(c->cmd1, c->cmd2, level, father)) == true);
		break;

	default:
		l_check(1, "unknown case", "c->op", 0, "error", -8);
		return SHELL_EXIT;
	}
	return result;
}
