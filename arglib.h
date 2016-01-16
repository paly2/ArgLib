/* Flags used by arg_filemane */
#define arg_FILENAME 1
#define arg_DIRNAME 2

char* arg_find_short(char *argv[], const char arg);
char* arg_find_short_one(char *argv[], const char arg);
char* arg_find_long(char *argv[], const char *arg);
char* arg_find_common(char *argv[], const char *arg);

int arg_is_short(const char *arg);
int arg_is_short_one(const char *arg);
int arg_is_long(const char *arg);
int arg_is_common(const char *arg);

char* arg_followed(char *argv[], char* previous);

char* arg_find_pathname(char *argv[], const int flags);
int arg_is_pathname(const char *arg, const int flags);
