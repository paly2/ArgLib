# ArgLib API examples

## 1. Find a specific argument

Code:

```
#include <stdio.h>
#include "arglib.h"

int main(int argc, char *argv[]) {
	char* arg = NULL;
	
	if ((arg = arg_find_short(argv, 'a')) != NULL)
		printf("Short argument (arg_find_short): %s\n", arg);
	else
		printf("No short argument \"a\" (arg_find_short).\n");
	
	if ((arg = arg_find_short_one(argv, 'b')) != NULL)
		printf("Short argument (arg_find_short_one): %s\n", arg);
	else
		printf("No short argument \"b\" (arg_find_short_one).\n");
	
	if ((arg = arg_find_long(argv, "long")) != NULL)
		printf("Long argument: %s\n", arg);
	else
		printf("No long argument \"long\".\n");
	
	if ((arg = arg_find_common(argv, "common")) != NULL)
		printf("Common argument: %s\n", arg);
	else
		printf("No common argument \"common\".\n");
	
	return 0;
}
```

Output:
> ./example1 --long common -eat -b  
> Short argument (arg_find_short): -eat  
> Short argument (arg_find_short_one): -b  
> Long argument: --long  
> Common argument: common

## 2. Find an argument following another one

Code:

```
#include <stdio.h>
#include "arglib.h"

int main(int argc, char *argv[]) {
	char* arg = NULL;
	
	if ((arg = arg_find_long(argv, "followed")) != NULL) {
		printf("Long argument: %s\n", arg);
		while ((arg = arg_followed(argv, arg)) != NULL)
			printf("Followed by common argument: %s\n", arg);
	}
	else
		printf("No long argument \"followed\".\n");
	
	return 0;
}
```

Output:
> ./example2 hello --followed my name is --paly2  
> Long argument: --followed  
> Followed by common argument: my  
> Followed by common argument: name  
> Followed by common argument: is

## 3. Find a file path argument

Code:

```
#include <stdio.h>
#include "arglib.h"

int main(int argc, char *argv[]) {
	char* filename = NULL;
	
	if ((filename = arg_find_filename(argv, arg_FILENAME)) != NULL)
		printf("First file path: %s\n", filename);
	else
		printf("No file path.\n");
	
	if ((filename = arg_find_filename(argv, arg_DIRNAME)) != NULL)
		printf("First directory path: %s\n", filename);
	else
		printf("No directory path.\n");
	
	if ((filename = arg_find_filename(argv, arg_FILENAME | arg_DIRNAME)) != NULL)
		printf("First file/directory path: %s\n", filename);
	else
		printf("No path.\n");
	
	return 0;
}
```

Output, if `folder` and `folder/file.txt` exist:
> ./example3 folder folder/file.txt  
> First file path: folder/file.txt  
> First directory path: folder  
> First file/directory path: folder

Output, if `folder` exists but `folder/file.txt` doesn't exist:
> ./example3 folder folder/file.txt  
> No file path.  
> First directory path: folder  
> First file/directory path: folder

Output, if `folder` and `folder/file.txt` don't exist:
> ./example3 folder folder/file.txt  
> No file path.  
> No directory path.  
> No path.

## 4. Know if an argument is short, long, common, a path...

Code:

```
#include <stdio.h>
#include "arglib.h"

int main(int argc, char *argv[]) {
	char* arg = NULL;
	int i = 0;
	
	if (!arg_is_short(argv[1]))
		printf("The first argument is not a short argument.\n");
	
	for (i = 1 ; i < argc ; i++)
		if (arg_is_filename(argv[i], arg_FILENAME))
			printf("%s is a file path.\n", argv[i]);
	
	return 0;
}
```

Output (if `file1.txt` and `file2.png` exist):
> ./example4 --ThisIsAVeryLongArgument file1.txt file2.png  
> The first argument is not a short argument.  
> file1.txt is a file path.  
> file2.png is a file path.
