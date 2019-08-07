#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chainedhashing.h"

//chained hashing ititilization
void init_chash(chash* h,int hash_entries)
{
	h->hashTable = (struct hash *) calloc(hash_entries, sizeof(struct hash));
	h->size = hash_entries;
}

//i , inserts record to hashtable too
void insertToHash(chash* h,int key, record* value)
{
    int hashIndex = key % (h->size);
    hnode* newnode = (hnode*)malloc(sizeof(hnode));
    newnode->key = key;
    newnode->value = value;
    newnode->next = NULL;

    /* head of list for the bucket with index "hashIndex" */
    if (!h->hashTable[hashIndex].head)
    {
        h->hashTable[hashIndex].head = newnode;
        h->hashTable[hashIndex].count = 1;
        return;
    }
    /* adding new node to the list */
    newnode->next = (h->hashTable[hashIndex].head);
    /*
     * update the head of the list and no of
     * nodes in the current bucket
     */
    h->hashTable[hashIndex].head = newnode;
    h->hashTable[hashIndex].count++;
    return;
}

//d, deletes from hash too
void deleteFromHash(chash* h,int key,int id)
{
    /* find the bucket using hash index */
    int hashIndex = key % h->size, flag = 0;
    hnode *temp, *myNode;
    /* get the list head from current bucket */
    myNode = h->hashTable[hashIndex].head;
    if (!myNode)
    {
//        printf("Given data is not present in hash Table!!\n");
        return;
    }
    temp = myNode;
    while (myNode != NULL) 
	{
        /* delete the node with given key */
        if (myNode->key == key) 
	{
	   if(myNode->value->studid == id)
	   {
           	flag = 1;
           	if (myNode == h->hashTable[hashIndex].head)
                	h->hashTable[hashIndex].head = myNode->next;
            	else
               	 	temp->next = myNode->next;

            	h->hashTable[hashIndex].count--;
//		printrecord(myNode->value);
	    	free(myNode->value);
		free(myNode);
            	break;
           }
	}
        temp = myNode;
        myNode = myNode->next;
    }
    return;
}


void searchInHash(chash* h,int key)
{
    int hashIndex = key % h->size, flag = 0;
    hnode*myNode;
    myNode = h->hashTable[hashIndex].head;
    if (!myNode)
    {
        printf("Search element unavailable in hash table\n");
        return;
    }
    while (myNode != NULL)
    {
       	if (myNode->key == key)
	{
		printrecord(myNode->value);
   	        flag = 1;
       		break;
        }
        myNode = myNode->next;
    }
    if (!flag)
        printf("Search element unavailable in hash table\n");
    return;
}

//iterates hash table
void display(chash* h)
{
    hnode *myNode;
    int i;
    for (i = 0; i < h->size; i++) {
        if (h->hashTable[i].count == 0)
            continue;
        myNode = h->hashTable[i].head;
        if (!myNode)
            continue;
        while (myNode != NULL) 
		{
			printrecord(myNode->value);
            myNode = myNode->next;
        }
    }
    return;
}

//a, students average gpa living on postcode 
void average(chash* h , int key)
{
//	printf("a %d \n",key);
	float  sum = 0.0 ;
	int counter = 0;
	int hashIndex = key % h->size;
	hnode *myNode;
	myNode = h->hashTable[hashIndex].head;
	if (!myNode)
    	{
    		return ;
    	}
    	else
    	{
        	while (myNode != NULL) 
		{
			sum = sum + myNode->value->gpa;
			counter++ ;
            		myNode = myNode->next;
        	}
	}
	float result = (float)sum/(float)counter ;
	printf("%.2f \n",result);
}

//percentile of students living on that postcode
void percentile(chash* h , int key ,int nos)
{
//	printf("p %d \n",key);
	int hashIndex = key % h->size;
	int students = h->hashTable[hashIndex].count;
	float result = (float)students/(float)nos ;
	printf("%d %.2f \n",key,result);
}

//p , percentiles of students living on each postcode
void percentiles(chash* h , int nos)
{
//  printf("pe \n");
    hnode *myNode;
    int i;
    for (i = 0; i < h->size; i++)
	{
        if (h->hashTable[i].count == 0)
            continue;
        myNode = h->hashTable[i].head;
        if (!myNode)
            continue;
        percentile(h ,h->hashTable[i].head->key,nos);
    }
    return;
}

//courses to take for each student living on posrtcode key and attending department deprt
void courses_to_take(chash* h , int key , char* deprt)
{
	//printf("ct %d %s \n",key,deprt);
	int hashIndex = key % h->size;
	hnode *myNode;
	myNode = h->hashTable[hashIndex].head;
	int f = 0 ;
	if (!myNode)
    	{
    		return ;
    	}
    	else
    	{
        	while (myNode != NULL)
		{
			if ( !(strcmp(myNode->value->deprt,deprt) ))
			{
				printrecord(myNode->value);
				printf("%d \n",myNode->value->numofcourses);
				f = 1;
			}
            		myNode = myNode->next;
        	}
		if ( !f )
			printf("not found\n");
	}
}

//ta, top k students living in postcode
//same as skiplist's bottom
void taverage(chash* h,int key,int k)
{
	printf("ta %d %d",k,key);
	int hashIndex = key % h->size;
	hnode * myNode;
	hnode* temp;
	myNode = h->hashTable[hashIndex].head;
	record** top = (record**)malloc(sizeof(record *) * k);
	int i,c;
	float max;
	for(i=0;i<k;i++)
	{
		top[i] = NULL;
	}
    	if (!myNode)
    	{
    		return ;
    	}
    	else
    	{
    		for(c = 0 ; c < k ; c++ )
    		{
			max = -1.0 ;
    			myNode = h->hashTable[hashIndex].head;
        		while (myNode != NULL) 
			{
				int f = 0 ;
				if( myNode->value->gpa > max )
				{
					int j;
					for( j=0; j<k  ;j++ )
					{
						if( myNode->value == top[j] )
						{
							f = 1 ;
							break;
						}
					}
					if ( !f )
					{
						max =  myNode->value->gpa;
						temp = myNode;
					}
				}
			myNode = myNode->next;
       	 	}
       	 	top[c] = temp->value ;
		}
		for(i=0;i<k;i++)
		{
			printrecord(top[i]) ;
		}
	}
}

//e , destoying hash table
void destroy_hash(chash* h)
{
    hnode *myNode;
    hnode* temp;
    int i;
    for (i = 0; i < h->size; i++)
	{
        if (h->hashTable[i].count == 0)
            continue;
        myNode = h->hashTable[i].head;
        if (!myNode)
            continue;
        while (myNode != NULL)
		{
			temp = myNode->next;
			free(myNode);
            myNode = temp;
        }
    }
 	free(h->hashTable);
}

