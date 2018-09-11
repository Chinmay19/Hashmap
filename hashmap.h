#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<assert.h>


typedef struct List
{
	struct List *next;
	void * val;
	const char * key;

}node;

typedef struct HashMaps
{
	node * head;
	int key_space;

}HashMap;

node * create_node();

HashMap * create_hashmap(size_t key_space);

uint32_t hash(const char *key);

void insert_data (HashMap *hm, const char *key, void *data, void *(*resolve_collision)(void *, void *));

void * get_data (HashMap *hm, const char *key);

void remove_data(HashMap *hm, const char *key, void(*destroy_data)(void *));

void iterate(HashMap *hm, void callback(void *,void *));

void delete_hashmap(HashMap *hm, void(*destroy_data)(void *));