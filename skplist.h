#ifndef __SKPLIST__
#define __SKPLIST__
#include "record.h"

//SKIPLIST
typedef struct snode
{
	int key;  /*key = arithmos mhtrwou */
	record* value;
	struct snode **forward;
}snode;

typedef struct skiplist
{
	int size;
    	struct snode *header;
	struct snode *term_node;
}skiplist;


void initialize_skiplist(skiplist *list);
record* skiplist_insert(skiplist *list, int key, record* value);
record *skiplist_search(skiplist *list, int key);
int skiplist_delete(skiplist *list,int key);
void raverage(skiplist *list, int low , int high);
void bottom(skiplist *list , int k);
void find(skiplist* list,float gpa);
void destroy_skiplist(skiplist* list);
#endif

