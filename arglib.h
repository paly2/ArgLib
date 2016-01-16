/* Flags used by arg_find_pathname and arg_is_pathname */
#define arg_FILENAME 1
#define arg_DIRNAME 2

/* The arg_kind enum. Note that you can use the values as flags for the arg_find function. */
typedef enum {SHORT_ONE = 1, SHORT = 2, LONG = 4, COMMON = 8, PATH = 16, ERROR = 32} arg_kind;

char* arg_find_short(char *argv[], const char arg);
char* arg_find_short_one(char *argv[], const char arg);
char* arg_find_long(char *argv[], const char *arg);
char* arg_find_common(char *argv[], const char *arg);
char* arg_find(char *argv[], const char *arg, const arg_kind kind);

int arg_is_short(const char *arg);
int arg_is_short_one(const char *arg);
int arg_is_long(const char *arg);
int arg_is_common(const char *arg);
arg_kind arg_how_is(const char *arg);

char* arg_followed(char *argv[], char* previous);

char* arg_find_pathname(char *argv[], const int flags);
int arg_is_pathname(const char *arg, const int flags);
