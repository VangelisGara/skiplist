#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "skplist.h"

#define SKIPLIST_MAX_LEVEL 4
#define MAX_VALUE 1000000

//Skiplist initialization: Empty skiplist.Creating header and term_node and assigns the right pointers to them
void initialize_skiplist(skiplist *list)
{
    	int i;
	snode *header = (snode *)malloc(sizeof(struct snode));
    	snode *term_node = (snode *)malloc(sizeof(struct snode));
	list->header = header;
    	list->term_node = term_node;
	header->key = 0;
	term_node->key = MAX_VALUE ;
    	header->forward = (snode **)malloc(sizeof(snode*) * (SKIPLIST_MAX_LEVEL));
    	term_node->forward  = (snode **)malloc(sizeof(snode*) * (SKIPLIST_MAX_LEVEL));
	for (i = 0; i <= SKIPLIST_MAX_LEVEL - 1; i++)
    	{
       		header->forward[i] = list->term_node;
		term_node->forward[i] = NULL;
    	}
	list->size = 0;
}

//i , inserting a record to the skiplist, based on algorithm given
record* skiplist_insert(skiplist *list, int key, record* value)
{
	snode *update[SKIPLIST_MAX_LEVEL];
	snode *x = list->header;
    	int i,level ;
    	for (i = SKIPLIST_MAX_LEVEL - 1 ; i >= 0; i--)
	{
       		while (x->forward[i]->key < key )
            	{
			x = x->forward[i];
        	}
		update[i] = x;
	}
    	x = x->forward[0];
	if (key == x->key)
	{
        	x->value = value;
        	return NULL;
    	}
	else
	{
        	level = rand() % SKIPLIST_MAX_LEVEL ;
		x = (snode *)malloc(sizeof(snode));
        	x->key = key;
        	x->value = value;
        	x->forward = (snode **)malloc(sizeof(snode*) * (level + 1));
        	for (i = 0; i <= level; i++)
		{
            		x->forward[i] = update[i]->forward[i];
            		update[i]->forward[i] = x;
        	}
    	}
    	//printf("\n Student : \n ");
	//printf("-----------------\n");
    	printrecord(x->value);
    	//printf("\n was inserted in skiplist \n");
    	list->size ++ ;
    	return x->value;
}

//q, searching a student in the skiplist
record *skiplist_search(skiplist *list, int key)
{
	//printf("q %d \n",key);
    	snode *x = list->header;
    	int i;
    	for (i = SKIPLIST_MAX_LEVEL - 1 ; i >= 0; i--)
	{
        	while (x->forward[i]->key < key)
		{
            		x = x->forward[i];
		}
    	}
   	x = x->forward[0];
    	if (x->key == key)
	{
    		//printf("\n -> Student Found \n");
        	return x->value;
   	}
	else
	{
        	return NULL;
    	}
    	return NULL;
}

//d, deleting student from skiplist
int skiplist_delete(skiplist *list,int key)
{
	//printf("d %d \n",key);
	int i; int postcode_to_return ;
    	snode *update[SKIPLIST_MAX_LEVEL];
    	snode *x = list->header;
    	for (i = SKIPLIST_MAX_LEVEL - 1 ; i >= 0; i--)
	{
    		while (x->forward[i]->key < key)
		{
            		x = x->forward[i];
		}
        	update[i] = x;
    	}
    	x = x->forward[0];
    	if (x->key == key)
	{
        	for (i = 0; i <= SKIPLIST_MAX_LEVEL - 1; i++) 
		{
            		if (update[i]->forward[i] != x)
			{
                		break;
			}
            		update[i]->forward[i] = x->forward[i];
        	}
        	if (x)
		{
			printrecord(x->value);
			postcode_to_return = x->value->postcode ;
        		free(x->forward);
        		free(x);
			list->size-- ;
    		}
        	return postcode_to_return;
    	}
	return 1;
}

/* About skiplist iteration to the following functions. I choose to iterate the list through
   the forward[0] pointers of skiplist , so I can have access to every single node of skiplist
   with one iteration only. */

//ra, iterates skiplists and checks if student's id is within limits given
void raverage(skiplist *list, int low , int high)
{
	//printf("ra %d %d \n",low,high);
   	snode *x = list->header;
    	float sum = 0;
    	int counter = 0;
    	while ( x->forward[0]->key != MAX_VALUE )
	{
		if ( x->forward[0]->key >= low && x->forward[0]->key <= high )
		{
			sum = sum + x->forward[0]->value->gpa ;
			counter++ ;
		}
		if ( x->forward[0]->key > high )
			break;
        	x = x->forward[0];
		if( x->forward[0]  == NULL) break;
	}
	float result ;
	result = (float)sum/(float)counter;
	printf("%.2f \n",result);
}

//b, iterates skiplist k times to find the k students with the least gpa
void bottom(skiplist *list , int k)
{
//	printf("b %d \n",k);
	snode* temp ;
	// Record array with the k worst students 
	record** btm = (record**)malloc(sizeof(record *) * k);
	int i,c;
	float min;
	for(i=0;i<k;i++)
	{
	   	btm[i] = NULL;
	}
	// For each c , we will find the least gpa
	for(c = 0 ; c < k ; c++ )
        {
    		snode *x = list->header;
		min = 11.0;
       		while ( x->forward[0]->key != MAX_VALUE )
		{
			int f = 0 ;
			if( x->forward[0]->value->gpa <=  min )
			{
				int j;
				// Checks if the student was already insertemd in the list 
				for( j=0; j<k  ;j++ )
				{
					if( x->forward[0]->value == btm[j] )
					{
						f = 1 ;
						break;
					}
				}
				//if student is already in , we ignore him , else we set him
				if ( !f )
				{
					min =  x->forward[0]->value->gpa;
					temp = x->forward[0] ;
				}
			}
                 	x = x->forward[0];
			if( x->forward[0]  == NULL) break;
		}
		//insertion into the array
        	btm[c] = temp->value ;
	}
	for(i=0;i<k;i++)
	{
		printrecord(btm[i]) ;
	}
}

//f,finds the students with the biggest number of courses,with gpa greater than a value
void find(skiplist* list,float gpa)
{
//	printf("f %2f \n",gpa);
   	snode *x = list->header;
    	float max = -1.0;
    	while ( x->forward[0]->key != MAX_VALUE )
	{
		if ( x->forward[0]->value->numofcourses > max )
		{
			max = x->forward[0]->value->numofcourses;
		}
		x = x->forward[0];
       		if( x->forward[0]->forward[0] == NULL ) break ;
	}
//	printf("%d",max);
 	x = list->header;
  	while ( x->forward[0]->key != MAX_VALUE )
	{
		if ( x->forward[0]->value->numofcourses == max )
		{
			if ( x->forward[0]->value->gpa > gpa )
			{
				printrecord(x->forward[0]->value);
			}
		}
		x = x->forward[0];
        	if( x->forward[0]->forward[0] == NULL ) break ;
	}
}

//e, destroys skiplist
void destroy_skiplist(skiplist* list)
{
	snode *x = list->header;
	snode *temp;
	x = x->forward[0];
   	while ( x->key != MAX_VALUE )
	{
		temp = x->forward[0];
		free(x->value);
		free(x);
        	x = temp;
	}
	free(list->header);
	free(list->term_node);
}
