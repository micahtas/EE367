#include <stdio.h>
#include <string.h>


#define x "This was my attempt at this assignment."

typedef struct node_t {
	struct node_t *left, *right;
	int freq;
	char c;
} *node;

struct node_t pool[256] = {{0}};
node qqq[255], *q = qqq -1;
int n_nodes = 0, qend = 1;
char *code[128] = {0}, buf[1024];

node new_node(int freq, char c, node a, node b)
{
	node n = pool + n_nodes++;
	if(freq) n->c = c, n->freq = freq;
	else {
		n->left = a, n->right = b;
		n->freq = a->freq + b->freq;
	}

	return n;
}

/* priority queue section */
void queue_insert(node n)
{
	int j, i = qend++;
	while((j=i/2)) {
		if(q[j]->freq <= n->freq) break;
		q[i] = q[j], i = j;
	}
	q[i] = n;
}

node queue_remove()
{
	int i, l;
	node n = q[i = 1];

	if(qend < 2) return 0;
	qend--;
	while((l = i*2) < qend) {
		if(l + 1 < qend && q[l +1]->freq < q[l]->freq) l++;
		q[i] = q[l], i = l;
	}
	q[i] = q[qend];
	return n;
}

/*traverse tree and insert 0/1*/
void create_code(node n, char *s, int len)
{
	static char *out = buf;
	if(n->c) {
		   s[len] = 0;
		   strcpy(out, s);
		   code[n->c] = out;
		   out += len +1;
		   return;
	}

	s[len] = '0'; create_code(n->left, s, len + 1);
	s[len] = '1'; create_code(n->right, s, len + 1);

}

void init(const char *s)
{
	int i, freq[128] = {0};
	char c[16];

	while(*s) freq[(int)*s++]++;

	for(i=0;i<128;i++)
		if(freq[i]) queue_insert(new_node(freq[i], i, 0, 0));

	while(qend>2)
		queue_insert(new_node(0, 0, queue_remove(), queue_remove()));

	create_code(q[1], c, 0);
}

void encode(const char *s, char *out)
{
	while(*s) {
		   strcpy(out, code[*s]);
		   out += strlen(code[*s++]);
	}
}

void decode(const char *s, node t)
{
	node n = t;
	while(*s) {
		   if(*s++ == '0') n = n->left;
		   else n = n->right;

		   if(n->c) putchar(n->c), n = t;
	}

	putchar('\n');
	if(t!=n) printf("bad input\n");
}

int main(int argc, char *argv[])
{
	int i;

	const char *str = x, buf[1024];
	init(str);
	for(i=0;i<128;i++)
		if(code[i])  printf("'%c': %s\n", i, code[i]);

	encode(str, buf);
	printf("encoded: %s\n", buf);

	printf("decoded: ");
	decode(buf, q[1]);

	return 0;
}
