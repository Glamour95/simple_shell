#ifndef SHELL_H
#define SHELL_H

int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int show_alias(list_t *node);
int _myalias(info_t *info);
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buffer, int linecount);
int renumber_history(info_t *info);
/*size_t list_len(const list_t *h);*/
char **list_to_strings(list_t *head);
/*size_t print_list(const list_t *h);*/
list_t *node_starts_with(list_t *node, char *prefix, char next_char);
char *starts_with(char *str, char *prefix);
int free_and_nullify(void **ptr);
char *_memset(char *dest, char value, unsigned int size);
void free(char **str_array);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

#endif
