/*
 * EE 367 Machine Program 2
 *
 * Author:  Galen Sasaki
 * Date:  January 23, 2013
 *
 * This program maintains a binary search tree.  It's to help you
 * understand pointers in C and search trees.
 *
 * The program first initializes a binary search tree. The
 * data in the node in the tree is a single text character
 * that ranges from 'a' to 'z'.  But initially, the tree is
 * empty.
 *
 * Then it gets comands from the user:
 *
 *   - (q) Quit
 *   - (e) Insert an alphabet
 *   - (d) Delete an alphabet
 *   - (t) List the nodes in the tree and their children
 *   - (i) List the nodes in in-order
 *   - (p) List the nodes in post-order
 *
 * The "(d) Delete" operation is not working.  If the node to delete is
 * a leaf then should delete.  Otherwise, it should not delete.
 * Also, "(p) List the nodes" in post-order is not working.
 * Your task is to make these work.
 *  
 *  You can compile by "gcc tree.c"
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct nodeType {
  char data;
  struct nodeType * left;
  struct nodeType * right;
} Node;

/* 
 * The following creates and destroys nodes using dynamic
 * memory allocation system calls 
 */
Node * createNode();  
void destroyNode(Node * nodeptr);

/* 
 * insertNode and deleteNode will insert and delete nodes.
 * addNode is called by insertNode, and searchNode is called
 * by deleteNode.
 * The deleteNode function is incomplete.  It only deletes
 * leaf nodes. One of your tasks is to have it be able to delete any
 * node in the tree. 
 */
void insertNode(Node ** ptr2link);
void addNode(Node * nodeptr, Node ** ptr2link);
void deleteNode(Node ** ptr2link);
Node ** searchNode(char c, Node ** ptr2link);

/*
 * listInOrder and listPostOrder will list the nodes in-order
 * and post-order.  One of your tasks is to implement
 * listPostOrder.  This is pretty easy, kind of a warm up
 * exercise.
 */
void listInOrder(Node * nodeptr);
void listPostOrder(Node * nodeptr);

/* 
 * displayTree will display the nodes of the tree and
 * their children.  This is useful to check if your
 * program is working and updating the tree properly.
 * It's also useful to identify nodes in the tree for
 * deleting.  For example, the current deleteNode function
 * only deletes leaves.  displayTree can be used
 * to determine which nodes are leaves.
 * displayTreeNodes is called by displayTree.
 */
void displayTree(Node * nodeptr);
void displayTreeNodes(Node * nodeptr);

main()
{

char cmd;   /* Command from user */
char c;
Node * head;  /* Head of the binary search tree */

head = NULL;  /* Initialize the binary search tree to be empty */

printf("Welcome to the binary search tree!\n\n");

while(1) {
   printf("Commands \n");
   printf("     (q) Quit\n");
   printf("     (e) Insert an alphabet \n");
   printf("     (d) Delete an alphabet \n");
   printf("     (t) Display tree \n");
   printf("     (i) List the nodes in in-order\n");
   printf("     (p) List the nodes in post-order\n");

   printf("Enter command: ");
   cmd = getchar();
   while(getchar() != '\n'); /* get rid of extra characters from stdin */

   if (cmd == 'q') return; /* Quit */
   else if (cmd == 'e') insertNode(&head);
   else if (cmd == 'd') deleteNode(&head); /* This is incomplete */
   else if (cmd == 't') displayTree(head);
   else if (cmd == 'i') { /* Display nodes in-order */
      printf("\n");
      printf("In-order list:");
      listInOrder(head);
      printf("\n\n");
   }
   else if (cmd == 'p') {
      	printf("\n");
      	printf("Post-order list:");
      	listPostOrder(head);
	printf("\n\n");
   }
   else {
      printf("Invalid command, try again\n");
   }
}
}


/* 
 * Create a node and return pointer to the node 
 */
Node * createNode()
{
Node * nodeptr;
nodeptr = (Node *) malloc(sizeof(Node));
nodeptr->left = NULL;
nodeptr->right = NULL;
return nodeptr;
}

/* 
 * Deallocate a node's space 
 */
void destroyNode(Node * nodeptr)
{
free(nodeptr);
}

/* 
 * The deleteNode is incomplete.  It only deletes nodes
 * that are leaves.  Otherwise, it doesn't change the tree.
 */
void deleteNode(Node ** ptr2link) 
{
Node ** nodeptrptr;
Node * nodeptr;

char c;

/* Get the alphabet to delete */
	while(1) 
	{
   		printf("Enter alphabet ('a' - 'z'): ");
   		c = getchar();
   		while(getchar() != '\n'); /* get rid of extra characters from stdin */
   		if (c < 'a' || c > 'z') printf("\n Try again \n");
   		else break;
	}

/* Search for the node */
	nodeptrptr = searchNode(c, ptr2link);
	if (nodeptrptr == NULL) return; /* Couldn't find it */

/* Delete the node */
	nodeptr = *nodeptrptr;
	if (nodeptr->left == NULL && nodeptr->right == NULL) 
	{ /* A leaf */
   		*nodeptrptr = NULL; /* Delete the node from the tree  by NULLing the
                          link from the parent node */
   		destroyNode(nodeptr); /* Deallocate space back to memory */
	}
	if(nodeptr->left != NULL || nodeptr->right != NULL)
	{
		printf("Not a leaf, re-enter desired letter to be deleted.\n");
	}
}

/* 
 * Searches for a node in the tree with data = c
 * Input:  data c
 *         Initially, ptr2link points to the head that points to first 
 *             node in the tree.  After that it points to the link
 *             that points to the node.  It's the same as nodeptrptr in
 *             the lecture notes.
 * Output: ptr to the link, that points to the node
 *         A return value of NULL indicates the node wasn't found
 */ 
Node ** searchNode(char c, Node ** ptr2link)
{

Node * nodeptr;

if (*ptr2link == NULL) return NULL;
else {
   nodeptr = *ptr2link; /* nodeptr points to the node */
   if (nodeptr->data == c) /* This is the node */
      return(ptr2link);
   else if (nodeptr->data > c) /* Search to the left */
      return searchNode(c, &(nodeptr->left));
   else /* Search to the right */
      return searchNode(c, &(nodeptr->right));
}
}


/* 
 * This listing is basically an in-order tree traversal 
 */
void listInOrder(Node * nodeptr)
{
if (nodeptr == NULL)  return; /* Nothing left to print */

listInOrder(nodeptr->left);
printf(" %c ",nodeptr->data);
listInOrder(nodeptr->right);
}


/* 
 * This needs to be implemented 
 */
void listPostOrder(Node * nodeptr)
{
	if(nodeptr == NULL) return;
	
	listPostOrder(nodeptr->right);
	printf(" %c ", nodeptr->data);
	listPostOrder(nodeptr->left);
}


/* 
 * Input:  newnodeptr points to the new node to insert
 *         Initially, ptr2link points to the head that points to first 
 *             node in the tree.  After that it points to the link
 *             that points to the node.  It's the same as nodeptrptr in
 *             the lecture notes.
 * Post Condition:  node is inserted into the binary search tree
 */ 
void addNode(Node * newnodeptr, Node ** ptr2link)
{
Node * nodeptr;

if (ptr2link == NULL) {
   printf("Something went wrong in addNode\n");
   return; 
}
else {
   nodeptr = *ptr2link; /* nodeptr points to a node in the tree */
   if (nodeptr == NULL) { /* insert new node */
      *ptr2link = newnodeptr;  /* This will change the value of a link in 
                               the tree */
      return;
   } 
   else if (nodeptr->data == newnodeptr->data) /* Node is already in tree */
      return;
   else if (nodeptr->data > newnodeptr->data) /* Search to the left */
      addNode(newnodeptr, &(nodeptr->left));
   else /* Search to the right */
      addNode(newnodeptr, &(nodeptr->right));
}
}


void insertNode(Node ** ptr2link)
{
char c;
Node * nodeptr;

while(1) {
   printf("Enter alphabet ('a' - 'z'): ");
   c = getchar();
   while(getchar() != '\n'); /* get rid of extra characters from stdin */
   if (c < 'a' || c > 'z') printf("\n Try again \n");
   else break;
}

/* Create a node */
nodeptr = createNode();
nodeptr->data = c;

/* Add the node to the binary search tree */
addNode(nodeptr, ptr2link);
}


void displayTree(Node * nodeptr)
{
printf("\nTree: (node)->[left child, right child]\n");
displayTreeNodes(nodeptr);
printf("\n");
}

void displayTreeNodes(Node * nodeptr)
{
Node * leftptr; 
Node * rightptr;

if (nodeptr == NULL) return;
else {
   /* Print current node and its children */
   printf("(%c)->",nodeptr->data);
   leftptr = nodeptr->left;
   if (leftptr==NULL) printf("[ ,");
   else printf("[%c,",leftptr->data);
   rightptr = nodeptr->right;
   if (rightptr==NULL) printf(" ]");
   else printf("%c]",rightptr->data);
   printf("\n");

   /* Continue printing descendent nodes */
   displayTreeNodes(leftptr);
   displayTreeNodes(rightptr);
}
}

