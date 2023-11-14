#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */

/* Global history counter */


/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	integer (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */


/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned integer old_size, unsigned integer new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
integer execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(integer num);

/* Input Helpers */
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, integer *exe_ret);
char *get_args(char *line, integer *exe_ret);
integer call_args(char **args, char **front, integer *exe_ret);
integer run_args(char **args, char **front, integer *exe_ret);
integer handle_args(integer *exe_ret);
integer check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* String functions */
integer _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
integer _strspn(char *s, char *accept);
integer _strcmp(char *s1, char *s2);
integer _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
integer (*get_builtin(char *command))(char **args, char **front);
integer shellby_exit(char **args, char **front);
integer shellby_env(char **args, char __attribute__((__unused__)) **front);
integer shellby_setenv(char **args, char __attribute__((__unused__)) **front);
integer shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
integer shellby_cd(char **args, char __attribute__((__unused__)) **front);
integer shellby_alias(char **args, char __attribute__((__unused__)) **front);
integer shellby_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
integer create_error(char **args, integer err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

integer proc_file_commands(char *file_path, integer *exe_ret);
#endif /* _SHELL_H_ */