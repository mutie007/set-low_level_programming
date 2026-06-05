i# 1. Create the file
nano 5-printf.c#include <stdio.h>

int main(void)
{
	printf("with proper grammar, but the outcome is a piece of art,\n");
	return (0);
}
# 2. Save and exit nano
CTRL + X, then Y, then ENTER

# 3. Compile
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 5-printf.c

# 4. Run
./a.out

# 5. Check return value
echo $?

