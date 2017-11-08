//  This program will keep a sorted list of names
//  It asks the user to either add an entry, delete
//  an entry, or display the list.  This is implemented
//  with a linked list and dynamic memory allocation.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definitions

typedef struct entry {
   char name[100];
   struct entry * next;
   } Entry; 

typedef struct {
   Entry * head; // Head which points to first element in list
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

do {
  command = getcommand();
  switch(command) {
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

  } while(command!='e');
}

void initlist(List *list)
{
list->head = NULL;
}

void deletelist(List *list)
{
	int result;
	Entry * deletentry;
	Entry * pos;
	Entry * prev;

	prev = list->head;
	deletentry = (Entry *) malloc(sizeof(Entry));	

	printf("Enter name to delete: ");
	scanf("%s", deletentry->name);
	while(getchar() != '\n') {}

	for(pos = list->head; pos != NULL; pos = pos->next)
	{
		result = strcmp(pos->name, deletentry->name);
		if(result == 0)
		{
			prev->next = pos->next;
			printf("Removed '%s'\n\n", deletentry->name);
		}
		else
		{
			printf("Name is not in list\n\n");
		}	
		prev = pos;
	}
	
}

void addlist(List *list)
{
int i;
int result;
char tempname[100];
Entry * newentryptr;
Entry ** lastptr;
Entry * pos;
Entry * prev;

newentryptr = (Entry *) malloc(sizeof(Entry));

if (newentryptr == NULL) {
   printf("Can't add to list, memory's full\n");
   return;
   }

// Initialize the new entry by getting a name from the user
// and making the next pointer equal NULL

printf("Enter new name: ");
scanf("%s",newentryptr->name);
while(getchar() != '\n') {}   // Get rid of spurious characters entered
                              //  by the user
newentryptr->next = NULL; 

// We'll insert the new entry into the end of the list 
// 
// Recall that each node in the linked list has the form [name, next].
// The linked list will look like
//
// head -> [name0,--]-> [name1,--]-> [name2, NULL] 
// 
// or head = NULL
//
// Initially, we want
//  
//  lastptr
//  |
//  V 
// head -> [name0,--]-> [name1,--]-> [name2, NULL] 
//
// But eventually, we want
//
//                                         lastptr
//                                            |
//                                            V
// head -> [name0,--]-> [name1,--]-> [name2, NULL] 

lastptr = &(list->head); // Initializes lastptr to point to head
while (* lastptr != NULL) {  // Stop if you're at the end
   lastptr = &((*lastptr)->next); // lastptr is updated so it points to
                               // the next node's "next" member.
}  
// Note that the above can be written as a for-loop to make the code
// even more compact

// Now we add the new entry

// Note that we already initialized the new node's next value to NULL 
	pos = list->head;
	result = -1;
	
	if(list->head == NULL)
	{
		* lastptr = newentryptr;
		printf("Added '%s' to the list\n\n", newentryptr->name);
	}
	else
	{
		for(pos = list->head; pos != NULL; pos = pos->next)
		{
			result = strcmp(pos->name, newentryptr->name);
			prev = pos;
		}
			if(result == 0)
			{
				printf("Name is already in list\n\n");
			}
			if(result != 0)
			{
				* lastptr = newentryptr;
				printf("Added '%s' to the list\n\n", newentryptr->name);
			}
			for(pos = list->head; pos != NULL; pos = pos->next)
			{
				result = strcmp(prev->name, pos->name);
					if(result > 0)
					{
						strcpy(tempname, pos->name);
						strcpy(pos->name, prev->name);
						strcpy(prev->name, tempname);
					}
				prev = pos;
			}
	}	
}

void displaylist(List *list)
{
Entry * listptr;

listptr = list->head;

if (listptr == NULL) {
   printf("List is empty\n");
   return;
   }

while (listptr != NULL) {
   printf("%s\n",listptr->name);
   listptr = listptr->next;
}

printf("\n");
}

char getcommand( )
{
char command;
int  valid;

do {
   printf("Enter command a(dd) d(elete) l(ist) h(help) or e(xit): ");
   command = getchar();
   while(getchar() != '\n') { } // Get rid of spurious characters
   switch(command){
      case 'a':
      case 'd':
      case 'e':
      case 'h':
      case 'l': valid = 1;
                break;
      default:  valid = 0;
                printf("Your entry '%c' is invalid!\n",command);
      }
   } while(valid == 0);

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

