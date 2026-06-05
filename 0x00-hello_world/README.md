Project Requirements!


Below are the requirements for this project:

Allowed editors: vi, vim, emacs
Compilation: Ubuntu 20.04 LTS using gcc with flags -Wall -Werror -Wextra -pedantic -std=gnu89
All files must end with a new line
A README.md file is required in the root of your repository and any new project directory you create
For C Files
Use C - Functions Betty style and follow both betty-style.pl and betty-doc.pl
No global variables
Maximum 5 functions per file
No use of system
For Shell Scripts
All your scripts should be exactly two lines long ($ wc -l file should print 2)
The first line of all your files should be exactly #!/bin/bash
All your file should be executable: chmod u+x file

## 2-assembler

This script generates the assembly code (`.s` file) from the C source file stored in the `$CFILE` environment variable.

### Usage:
```bash
export CFILE=main.c
./2-assembler

