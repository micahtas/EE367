/*
 * Homework 5.  You are to implement Problems 5 and 6 from
 * Homework 3.  Find the functions inserNearEnd and reverseList
 * and implement them.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct listnode {
   char data;
   struct listnode * next;
} Node;

Node * create()
/* Creates a link node */
{
return (Node *)malloc(sizeof(Node));
}

void destroy(Node * nodeptr)
/* Destroys a link node */
{
free(nodeptr);
}

void display(Node * head)
/* Displays linked list.  Assumes head is the head of the linked list */
{
Node * nodeptr;

printf("List: ");
nodeptr = head;
while (nodeptr != NULL) {
   printf("->[%c]",nodeptr->data);
   nodeptr=nodeptr->next;
}
printf("\n");
}

void destroylist(Node ** headptr)
/* Destroys all nodes in the list */
{
Node * nodeptr;
Node * current;
nodeptr = *headptr;
while (nodeptr != NULL) {
   current = nodeptr;
   nodeptr = nodeptr->next;
   destroy(current);
}
*headptr = NULL;
}

void filllist(Node ** headptr)
/*
 * Fill a linked list with 'a', 'b',..., 'j'
 */
{
Node ** nodeptrptr;
char c;

nodeptrptr = headptr;
for (c='a'; c<='j'; c++) {
   *nodeptrptr = create();
   (*nodeptrptr)->data = c;
   nodeptrptr = &((*nodeptrptr)->next); 
}
*nodeptrptr=NULL;
}

void insertNearEnd(Node ** headptr, Node * nodeptr)
/* 
 * Inserts node (nodeptr) into the next to last node 
 * in linked list (headptr) 
 */
{ 
	Node * head;
	Node * last;
	
	head = *headptr;
	last = NULL;

	while(head->next->next != NULL)
	{
		head = head->next;
	}
	
	nodeptr->next = head->next;
	head->next = nodeptr;
}

void reverseList(Node ** headptr)
/* Reverses linked list.  Implement problem 6 of homework 3 */
{
	Node * head;
	Node * last;
	Node * temp;

	head = *headptr;
	last = NULL;

	while(head != NULL)
	{
		temp = head->next;
		head->next = last;
		last = head;
		head = temp;
	}
	
	*headptr = last;
}

main()
{

Node * head; /* Head of the linked list */
Node * newptr;

/* Create linked list and fill it with 'a', 'b', ..., 'j' */
head = NULL;
filllist(&head);

printf("\nInitial list\n");
display(head);

newptr = create();
newptr->data = 'x';
newptr->next = NULL;

insertNearEnd(&head, newptr);
printf("Insert 'x' the next to the last node: between 'i' and 'j'\n");
display(head);
destroylist(&head);

printf("\nInitial list\n");
filllist(&head); /* Initialize list */
display(head);

reverseList(&head);
printf("Reversed list\n");
display(head);

destroylist(&head);
}

