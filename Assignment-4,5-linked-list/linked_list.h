#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdlib.h>

struct l_list {
	int value;
	struct l_list *next;
};

typedef struct l_list l_list;

l_list *list_create(int val);
l_list *list_add_front(int value, l_list **m_list);
l_list* list_add_back(int value, l_list** m_list);

l_list* list_add_after(l_list* node, int value);

l_list* list_node_at(int index, l_list* list);
int list_get(l_list* list,int index);
void list_free(l_list* list);
int list_lenght(l_list* list);
int list_sum(l_list* list);

void foreach(l_list* list, void (*consumer)(int));
l_list* map(l_list* list, int (*operator)(int));
l_list* map_mut(l_list** list, int (*operator)(int));


int foldl(l_list* list, int acc, int (*operator)(int, int));
l_list* iterate(int value, size_t length, int (*operator)(int));
int save(l_list* list, const char* filename);
int load(l_list** list, const char* filename);
int serialize(l_list* list, const char* filename);
int deserialize(l_list** list, const char* filename);

#endif