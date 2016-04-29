# ArgLib API

In this file :  
A "long argument" is an argument prefixed by "--" and described by many characters.  
A "short argument" is an argument prefixed by "-" and described by only one chacter.  
A "common argument" is an argument which is neither a long argument, nor a short argument. Note a common argument can be a file path.  
A "file path argument" is an argument which specifies a file/directory path.

Every chapter of this file has an example of the `examples.md` file.

## 1. To find a specific argument

### 1.1. To find a long argument

To know if a long argument is passed to the program, you can use the function :

```
char* arg_find_long(char *argv[], const char *arg);
```

* Parameter 1 : argv (strings array), the arguments table.
* Parameter 2 : arg (string), the long argument.
* Return value : (string), the complete argument where arg was found, or NULL if arg was not found.

### 1.2. To find a short argument

To know if a short argument is passed to the program, you can use the function :

```
arg_find_short_one(char *argv[], const char arg);
```

* Parameter 1 : argv (strings array), the arguments table.
* Parameter 2 : arg (character), the short argument. *Remenber this is just a character and not a string.*
* Return value : (string), the complete argument where arg was found, or NULL if arg was not found.

Note: There can be many short arguments introduced by the same "-". If you want not, use the `arg_find_short_one` function instead.

### 1.3. To find a common argument

To know if a common argument is passed to the program, you can use the function :

```
char* arg_find_common(char *argv[], const char *arg);
```

* Parameter 1 : argv (strings array), the arguments table.
* Parameter 2 : arg (string), the common argument.
* Return value : (string), the complete argument where arg was found, or NULL if arg was not found.

### 1.4. These functions are deprecated !

You should use the function :
```
char* arg_find(char *argv[], const char *arg, const arg_kind kind);
```

* Parameter 1 : argv (strings array), the arguments table.
* Parameter 2 : arg (string), the argument.
* Parameter 3 : kind (`arg_kind` enum), the kind of the argument (COMMON, SHORT, SHORT_ONE or LONG).
* Return value : (string), the complete argument where arg was found, or NULL if arg was not found.

Note: You can use the `arg_kind` enum values as flags in the third parameter (for example, `LONG|COMMON` will allow the function to return a long or a common argument.
Other note: For a short argument, the function uses only the first character of the arg string.

## 2. To find an argument following another one

To find an argument wich follows another one, you can use the function :

```
char* arg_followed(char *argv[], char *previous);
```

* Parameter 1 : argv (strings array), the arguments table.
* Parameter 2 : previous (string), the previous argument. **Please always use the return value of an arg_find* function for this parameter. If you don't, you may get a segment error.**
* Return value : (string), the next argument, or NULL if it was not found.

Note: The next argument must always be a common argument.

## 3. To find a file path argument

To find a file path argument, you can use the function :

```
char* arg_find_pathname(char *argv[], const int flags);
```

* Parameter 1 : argv (strings array), the arguments table.
* Parameter 2 : flags (number made by flags), the kind of path :
 * `arg_FILENAME` : the path is a file path ;
 * `arg_DIRNAME` : the path is a directory path ;
 * you can mix the flags like this : `arg_FILENAME | arg_DIRNAME` : the path is either a file path, or a directory path.
* Return value : (string), the first path found, or NULL if no path was found.

## 4. To know if an argument is short, long, common, a path...

Every `arg_find_*` prefixed function has a `arg_is_*` version with this prototype :

```
int arg_is_(short|short_one|long|common)(const char *arg);
int arg_is_pathname(const char *arg, const int flags);
```

* Parameter 1 : arg (string), the argument.
* Return value : (boolean), 1 : true, 0 : false

However, these functions are now deprecated and you should use the function :
```
arg_kind arg_how_is(const char *arg);
```

* Parameter 1 : arg (string), the argument.
* Return value : (`arg_kind` enum), the kind of the argument, (COMMON, SHORT, SHORT_ONE, LONG, PATH or ERROR).

Note: If the argument is short but has only one character, the function will return SHORT_ONE. However, if you want to know if the function returns SHORT_ONE or SHORT, you can test `arg_how_is(arg) <= SHORT` instead of `arg_how_is(arg) == SHORT_ONE || arg_how_is(arg) == SHORT` because SHORT and SHORT_ONE are the two smallest values of the enumeration.
