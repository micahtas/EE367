//  This program will keep a sorted list of names
//  It asks the user to either add an entry, delete
//  an entry, or display the list.
//

#include <stdio.h>
#include <string.h>

// Definitions

#define MAXLIST 100 // Maximum size of list

typedef struct entry 
{
	char name[100];
} Entry; 

typedef struct 
{
   	Entry person[MAXLIST];
   	int count;
} List;

// Function prototypes
char getcommand();
void initlist(List *list);
void addlist(List *list);
void displaylist(List *list);
void deletelist(List *list);
void help();

main()
{
char command;
List list;

initlist(&list);

do 
{
  	command = getcommand();
 	switch(command) 
	{
     		case 'a': addlist(&list);
               	break;
     		case 'd': deletelist(&list);
               	break;
     		case 'l': displaylist(&list);
               	break;
     		case 'h': help();
               	break;
     		case 'e': printf("Exiting program\n");
     	} 

} 
while(command != 'e');
}

void initlist(List *list)
{
	list->count = 0;
}

void deletelist(List *list)
{
	int i = 0;
	int pos = 0;
	int result;
	char deletename[100];

	printf("Enter name desired to be deleted: ");
	scanf("%s", deletename);

	while(getchar() != '\n') {}

	for(i = 0; i < MAXLIST; i++)
	{
		result = strcmp(list->person[i].name, deletename);
		if(!result)
		{
			strcpy(list->person[i].name, deletename);
			pos = i;
			printf("Deleted name %s. \n", list->person[i].name);

			for(i = pos; i < MAXLIST; i++)
				strcpy(list->person[i].name, list->person[i+1].name);
		}
	}
}

void addlist(List *list)
{
int i;
int result;
char newname[100];
char tempname[100];

if (list->count >= MAXLIST) 
{
   	printf("Can't add to list, it's full\n");
   	return;
}

// Get a name from the user and add to end of list
printf("Enter new name: ");
scanf("%s",newname);
while(getchar() != '\n') {}   // Get rid of spurious characters entered
                              //  by the user

// Now that we have the "newname", we'll insert it into the list
// in two steps
//
// Step 1. We'll add it to the end of the list

i = list->count;              // End of the list
strcpy( list->person[i].name, newname); 
list->count++;

// Step 2.  newname is now at the end of the list but
// it may be out of order.  So we'll move it into sorted
// order as followws.  We'll start at the end of the list,
// which is the location of newname initially.  We check
// if newname is in proper order with respect to the
// previous element in the list.  If it is then we stop.
// Otherwise, we swap newname with that previous element.
// Next, we compare newname with the next previous element.
// If newname is in proper order then we stop.  Otherwise,
// we swap newname with the other element.  We continue
// in this way until we reach the beginning of the list. 
//

for (i = list->count - 2; i >= 0; i--) 
{  // "i" is newname's location
   // Check if entry i is greater than entry i+1
   // Note:  strcmp returns 
   //    0        if the strings are the same,
   //    neg val  if entry i is less than entry i+1
   //    pos val  if entry i is greater than entry i+1
   
	result = strcmp(list->person[i].name,list->person[i+1].name);
   	if (result > 0) 
	{ // Swap values since i and i+1 are in wrong order
      		strcpy(tempname, list->person[i].name);
      		strcpy(list->person[i].name,list->person[i+1].name);
      		strcpy(list->person[i+1].name,tempname); 
      	}     
} 

printf("Added '%s' to the list\n\n",newname);
}

void displaylist(List *list)
{
int i;

if (list->count < 1) 
{
   	printf("List is empty\n");
   	return;
}

for (i = 0; i < list->count; i++) 
{
   	printf("%s\n", list->person[i].name);
}
	printf("\n");
}

char getcommand( )
{
char command;
int  valid;

do 
{
   	printf("Enter command a(dd) d(elete) l(ist) h(help) or e(xit): ");
   	command = getchar();
   	while(getchar() != '\n') { } // Get rid of spurious characters
   	switch(command)
	{
      		case 'a':
      		case 'd':
      		case 'e':
      		case 'h':
      		case 'l': valid = 1;
                break;
      		default:  valid = 0;
                	printf("Your entry '%c' is invalid!\n",command);
      	}
} 
while(valid == 0);

return(command);
}

void help()
{
printf("\nDescription of commands\n");
printf("   a:  Add a name to the list\n");
printf("   d:  Delete a name from the list\n");
printf("   l:  Lists the list, which should be sorted\n");
printf("   e:  Exits the program\n");
printf("\n");
}

