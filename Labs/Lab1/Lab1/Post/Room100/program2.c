/*
This is program compiles perfectly the function
is defined before it is called.
*/
#include <stdio.h>

void hello()
{
printf("Hello world\n");
}

main()
{
hello();
}

