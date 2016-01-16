/* Flags used by arg_find_pathname and arg_is_pathname */
#define arg_FILENAME 1
#define arg_DIRNAME 2

typedef enum {COMMON, SHORT, SHORT_ONE, LONG, PATH, ERROR } arg_kind;

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
