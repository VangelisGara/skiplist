#ifndef __CHAINEDHASHING__
#define __CHAINEDHASHING__
#include "record.h"

//hash node 
typedef struct hnode 
{
	int key;
	record* value;
	struct hnode* next;
}hnode;

//array's structs , contains the head of the list and counts the size of list
struct hash
{
	hnode* head;
	int count;
};

//contains the hash table and its HASH_ENTRIES
typedef struct chash
{
	struct hash* hashTable  ;
	int size ;
}chash;

void init_chash(chash* h,int hash_entries);
void insertToHash(chash* h,int key, record* value);
void deleteFromHash(chash* h,int key,int id);
void searchInHash(chash* h,int key);
void display(chash* h);
void average(chash* h , int key);
void percentile(chash* h , int key ,int nos);
void percentiles(chash* h , int nos);
void courses_to_take(chash* h , int key , char* deprt);
void taverage(chash* h,int key,int k);
void destroy_hash(chash* h);
#endif
