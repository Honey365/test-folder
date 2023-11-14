#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	integer num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	integer argc;
	unsigned int line_count;
	integer err_num;
	integer linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	integer env_changed;
	integer status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	integr cmd_buf_type; /* CMD_type ||, &&, ; */
	integer readfd;
	integer histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	integer (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
integer hsh(info_t *, char **);
integer find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
integer is_cmd(info_t *, char *);
char *dup_chars(char *, integer, integer);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
integer loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
integer _eputchar(char);
integer _putfd(char c, integer fd);
integer _putsfd(char *str, integer fd);

/* toem_string.c */
integer _strlen(char *);
integer _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
integer _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, integer);
char *_strncat(char *, char *, integer);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned integer);
void ffree(char **);
void *_realloc(void *, unsigned integer, unsigned integer);

/* toem_memory.c */
integer bfree(void **);

/* toem_atoi.c */
integer interactive(info_t *);
integer is_delim(char, char *);
integer _isalpha(integer);
integer _atoi(char *);

/* toem_errors1.c */
integer _erratoi(char *);
void print_error(info_t *, char *);
integer print_d(integer, integer);
char *convert_number(long integer, integer, integer);
void remove_comments(char *);

/* toem_builtin.c */
integer _myexit(info_t *);
integer _mycd(info_t *);
integer _myhelp(info_t *);

/* toem_builtin1.c */
integer _myhistory(info_t *);
integer _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
integer _getline(info_t *, char **, size_t *);
void sigintHandler(integer);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, integer);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
integer _myenv(info_t *);
integer _mysetenv(info_t *);
integer _myunsetenv(info_t *);
integer populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
integer _unsetenv(info_t *, char *);
integer _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
integer write_history(info_t *info);
integer read_history(info_t *info);
integer build_history_list(info_t *info, char *buf, integer linecount);
integer renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, integer);
list_t *add_node_end(list_t **, const char *, integer);
size_t print_list_str(const list_t *);
integer delete_node_at_index(list_t **, unsigned integer);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
integer replace_alias(info_t *);
integer replace_vars(info_t *);
integer replace_string(char **, char *);

#endif
