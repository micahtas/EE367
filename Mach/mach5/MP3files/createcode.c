#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define x "Attempt at assignment"

typedef struct node
{
	struct node *left;
	struct node *right;
	int freq;
	char c;
} *node;

int n_node = 0, q_end = 1;
node qq[255], *q = qq - 1;
char *code[128] = {0}, buff[1024];
struct node pool[256] = {{0}};

node new_node(int freq, char c, node a, node b)
{
	node n = pool + n_node++;
	
	if(freq)
	{
		n->c = c;
		n->freq = freq;
	}
	else
	{
		n->left = a;
		n->right = b;
		n->freq = a->freq + b->freq;
	}

	return n;
}

void queue_insert(node n)
{
	int i = q_end++;
	int j;

	while((j = i/2))
	{
		if(q[j]->freq <= n->freq)
			break;
		q[i] = q[j];
		i = j; 
	}

	q[i] = n;
}

node queue_remove()
{
	int i;
	int j;
	node n = q[i = 1];

	if(q_end < 2)
		return 0;
		q_end--;

	while((j = i*2) < q_end)
	{
		if(j + 1 < q_end && q[j+1]-> freq < q[j]->freq)
			j++;
			q[i] = q[j];
			i = j;
	}

	q[i] = q[q_end];
	return n;
}

void create_code(node n, char *s, int length)
{
	static char *out = buff;
	
	if(n->c)
	{
		s[length] = 0;
		strcpy(out, s);
		out += length + 1;
		return;
	}

	s[length] = '0';
	create_code(n->left, s, length + 1);
	s[length] = '1';
	create_code(n->right, s, length + 1);
}

void init(const char *s)
{
	int i;
	int freq[128] = {0};
	char c[16];

	while(*s)
		freq[(int)*s++]++;

	for(i = 0; i < 128; i++)
		if(freq[i])
			queue_insert(new_node(freq[i], i, 0, 0));

	while(q_end > 2)
		queue_insert(new_node(0, 0, queue_remove(), queue_remove()));

	create_code(q[1], c, 0);
}

void encode(const char *s, char *out)
{
	while(*s)
	{
		strcpy(out, code[*s]);
		out += strlen(code[*s++]);
	}
}

void decode(const char *s, node t)
{	
	node n = t;
	while(*s)
	{
		if(*s++ == '0')
			n = n->left;
		else
			n = n->right;

		if(n->c)
			putchar(n->c), n = t;
	}

	putchar('\n');
	if(t != n)
		printf("Bad Input\n");
}

int main(int argc, char *argv[])
{
	FILE *fp, *fp2;
	char ch;
	int t;
	
	if(argc <= 2)
	{
		printf("Usage:\n %s <input-file-to-zip> <zipped-output-file>\n", argv[0]);

		if(argc == 2)
		{
			argv[2] = (char *)malloc(sizeof(char)*(strlen(argv[1]) + str(ext) +1));
			strcpy(argv[2], argv[1]);
			strcat(argv[2], ext);
			argc++;
		}
		else
			return 0;
	}

	fp = fopen(argv[1], "rb");
	
	if(fp == NULL)
	{
		printf("[!] Input files cannot be opened.\n");
		return -1;
	}

	
}

