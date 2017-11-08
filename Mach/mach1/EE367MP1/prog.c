/*  
 *  First sample program from the first youtube tutorial on gdb
 *  The youtube tutorial is by "csurendar"
 *
 *  This has a single bug where a char pointer *ptr is set to NULL.
 *  Then *ptr (dereferencing pointer ptr) is set to the value 0,
 *  which will try to access memory pointed to by ptr.  Since
 *  ptr doesn't point to anything, you should get a segmentation
 *  error.
 */

#include <stdlib.h>

nop()
{
/* step vs next command */
}

func1(int arg)
{
func2 (arg+1);
}

func2(int arg)
{
int val = arg;
char *ptr = NULL;  /* Here is part of the bug, setting ptr to NULL */

if (val > 0)
   *ptr = 0;      /* This is where you will get segmentation error */
else {
   ptr = (char *) malloc(10);
   nop();
   *ptr = 0;
}
}

main()
{
   func1(1);
}


