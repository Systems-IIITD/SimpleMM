#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include "memory.h"

#undef malloc
#undef free

#define MAX_NODES 100000
#define MAX_REPLACEMENTS 1000000

size_t total_mem = 0;

struct node {
	int size;
	int id;
};

static int num_nodes = MAX_NODES;
static int num_replacements = MAX_REPLACEMENTS;

struct node* allocate_n(int id)
{
	size_t size = sizeof(struct node) + (rand() % 4096);
	struct node *n = (struct node*)mymalloc(size);
	total_mem += size;
	if (n == NULL)
	{
		printf("unable to allocate new node\n");
		exit(0);
	}
	n->size = size;
	n->id = id;
	return n;
}

void replace(struct node *nodes[])
{
	int i = rand() % num_nodes;
	struct node *original = nodes[i];
	assert(original->id == i);
	total_mem -= original->size;
	myfree(original);
	nodes[i] = allocate_n(i);
}

int main(int argc, char *argv[])
{
	int i;
	assert(argc <= 4);

	if (argc >= 2) {
		num_replacements = atoi(argv[1]);
		assert(num_replacements > 0);
	}
	printf("num replacements:%d\n", num_replacements);

	struct node **nodes = mymalloc(sizeof(struct node*) * num_nodes);
	if (nodes == NULL)
	{
		printf("unable to allocate nodes array!\n");
		return 0;
	}

	for (i = 0; i < num_nodes; i++)
	{
		nodes[i] = allocate_n(i);
	}

	for (int i = 0; i < num_replacements; i++)
	{
		replace(nodes);
	}

	for (i = 0; i < num_nodes; i++)
	{
		assert(nodes[i]);
		total_mem -= nodes[i]->size;
		myfree(nodes[i]);
	}
	myfree(nodes);
	printf("remain mem:%zd\n", total_mem);
	return 0;
}
