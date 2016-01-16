#include <string.h>
#include <sys/stat.h>
#include "arglib.h"

char* arg_find_short(char *argv[], const char arg) {
	int i;
	for (i = 1 ; argv[i] != NULL && i < 500 ; i++) {
		if (arg_is_short(argv[i]) && strchr(argv[i]+1, arg) != NULL)
			return argv[i];
	}
	
	return NULL;
}

char* arg_find_short_one(char *argv[], const char arg) {
	int i;
	for (i = 1 ; argv[i] != NULL && i < 500 ; i++) {
		if (arg_is_short_one(argv[i]) && strchr(argv[i]+1, arg) != NULL)
			return argv[i];
	}
	
	return NULL;
}

char* arg_find_long(char *argv[], const char *arg) {
	int i;
	for (i = 1 ; argv[i] != NULL && i < 500 ; i++) {
		if (arg_is_long(argv[i]) && strcmp(argv[i]+2, arg) == 0)
			return argv[i];
	}
	
	return NULL;
}

char* arg_find_common(char *argv[], const char *arg) {
	int i;
	for (i = 1 ; argv[i] != NULL && i < 500 ; i++) {
		if (arg_is_common(argv[i]) && strcmp(argv[i], arg) == 0)
			return argv[i];
	}
	
	return NULL;
}

int arg_is_short(const char *arg) {
	if (arg == NULL)
		return 0;
	
	if (strlen(arg) < 2)
		return 0;
	
	if (arg[0] == '-' && arg[1] != '-')
		return 1;
	else
		return 0;
}

int arg_is_short_one(const char *arg) {
	if (arg == NULL)
		return 0;
	
	if (arg_is_short(arg) && strlen(arg) == 2)
		return 1;
	else
		return 0;
}

int arg_is_long(const char *arg) {
	if (arg == NULL)
		return 0;
	
	if (strlen(arg) < 4)
		return 0;
	
	if (arg[0] == '-' && arg[1] == '-')
		return 1;
	else
		return 0;
}

int arg_is_common(const char *arg) {
	if (arg == NULL)
		return 0;
	
	if (!arg_is_short(arg) && !arg_is_long(arg))
		return 1;
	else
		return 0;
}

char* arg_followed(char *argv[], char *previous) {
	if (previous == NULL)
		return NULL;
	
	/* We need to check if previous is the last argument. */
	int argc;
	for (argc = 0 ; argv[argc] != NULL ; argc++);
	if (argv[argc-1] <= previous)
		return NULL;
	
	const char *next = previous+strlen(previous)+1;
	if (arg_is_common(next))
		return (char*)next;
	else
		return NULL;
}

char* arg_find_pathname(char *argv[], const int flags) {
	int i;
	for (i = 1 ; argv[i] != NULL && i < 500 ; i++) {
		if (arg_is_pathname(argv[i], flags))
			return argv[i];
	}
	
	return NULL;
}

int arg_is_pathname(const char *arg, const int flags) {
	if (arg == NULL)
		return 0;
	
	struct stat sb;
	if (stat(arg, &sb) == -1)
		return 0;
	
	if ((sb.st_mode & S_IFMT) == S_IFREG && flags & arg_FILENAME)
		return 1;
	else if ((sb.st_mode & S_IFMT) == S_IFDIR && flags & arg_DIRNAME)
		return 1;
	else
		return 0;
}

