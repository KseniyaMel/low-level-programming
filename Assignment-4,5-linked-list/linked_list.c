#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>

#include "linked_list.h"

l_list* list_create(int val) {
	l_list* list = malloc(sizeof(l_list));
	list->value = val;
	list->next = NULL;
	return list;
}

l_list* list_add_front(int value, l_list** m_list) 
{
	l_list *list = list_create(value);
	list->next = *m_list;
	*m_list = list;

	return list;
}

l_list* list_add_back(int value, l_list** m_list) 
{
	l_list* count = *m_list;
	
	if (*m_list == NULL)
	{
		*m_list = count;
	} else {
		l_list *iter = *m_list;
		while(iter->next !=NULL) iter = iter->next;
		iter->next = count;
	}

	return count;
}

l_list* list_add_after(l_list* node, int value) 
{
    l_list* new_node = list_create(value);

    if (node != NULL) 
    {
        new_node->next = node->next;
        node->next = new_node;
    }

    return new_node;
}


l_list* list_node_at(int index, l_list* list)
{
	l_list* count = list;
	int i = 0;

	while (count->next != NULL) 
    {
		if (index == i) break;

		count = count->next;
		i += 1;
	}

	if (index != i) return 0;

	return count;
}


int list_get(l_list* list, int index)
{
	l_list* count = list;
	int i = 0;

	while (count->next != NULL) 
    {
		if (index == i) break;

		count = count->next;
		i += 1;
	}

	if (index != i) return 0;

	return count->value;
}

void list_free(l_list* list) 
{
	while (list->next != NULL) 
    {
		l_list* died = list;
		list = list->next;

		free(died);
	}
}

int list_lenght(l_list* list) 
{
	l_list* count;
	int len = 0;

	for (count = list; count != NULL; count = count->next)
		++len;

	return len;
}

int list_sum(l_list* list)
{
	l_list* count = list;
	int sum = 0;

	if (count == NULL) return sum;

	for (;;)
	{
		sum += count->value;
		if (count->next == NULL) break;
		count = count->next;
	}

	return sum;
}

void foreach(l_list* list, void (*procedure)(int)) 
{
	l_list* count;

	for (count = list; count != NULL; count = count->next)
		procedure(count->value);
}

l_list* map(l_list* list, int (*operator)(int)) 
{
	l_list* count, * new_count = NULL, * start = NULL;

	for (count = list; count != NULL; count = count->next) 
    {
		new_count = list_add_after(new_count, operator(count->value));

		if (start == NULL) start = new_count;
	}

	return start;
}

l_list* map_mut(l_list** list, int (*operator)(int)) 
{
	l_list* count;

	for (count = *list; count != NULL; count = count->next)
		count->value = operator(count->value);

	return *list;
}

int foldl(l_list* list, int acc, int (*operator)(int, int)) 
{
    l_list* count;

    for (count = list; count != NULL; count = count->next)
        acc = operator(count->value, acc);

    return acc;
}


l_list* iterate(int value, size_t length, int (*operator)(int)) 
{
    size_t i;
    l_list* start, * count;

    start = list_create(value);
    count = start;

    for (i = 1; i < length; i++) 
    {
        value = operator(value);
        count = list_add_after(count, value);
    }

    return start;
}

int save(l_list* list, const char* filename) 
{
    l_list* count;

    FILE* f;
    errno = 0;
    f = fopen(filename, "w");
    if (errno) return 0;

    for (count = list; count != NULL; count = count->next) 
    {
        fprintf(f, "%d ", count->value);

        if (errno || ferror(f)) 
        {
            fclose(f);
            return 0;
        }
    }

    fclose(f);

    if (errno) return 0;
    return 1;
}

int load(l_list** list, const char* filename) 
{
    l_list* count = NULL, * start = NULL;
    int value;

    FILE* f;
    errno = 0;
    f = fopen(filename, "r");
    if (errno) return 0;

    for(;;)
    {
        fscanf(f, "%d", &value);

        if (feof(f)) break;

        if (errno || ferror(f)) 
        {
            fclose(f);
            return 0;
        }

        count = list_add_after(count, value);

        if (start == NULL) start = count;
    }

    *list = start;
    fclose(f);

    if (errno) return 0;
    return 1;

}

int serialize(l_list* list, const char* filename) 
{
    l_list* count;

    FILE* f;
    errno = 0;
    f = fopen(filename, "wb");
    if (errno) return 0;

    for (count = list; count != NULL; count = count->next) 
    {
        fwrite(&count->value, sizeof(int), 1, f);

        if (errno || ferror(f)) 
        {
            fclose(f);
            return 0;
        }
    }

    fclose(f);

    if (errno) return 0;
    return 1;

}

int deserialize(l_list** list, const char* filename) 
{
    l_list* count = NULL, * start = NULL;
    int value;

    FILE* f;
    errno = 0;
    f = fopen(filename, "r");
    if (errno) return 0;

    for(;;)
    {
        fread(&value, sizeof(int), 1, f);

        if (feof(f)) break;

        if (errno || ferror(f))
        {
            fclose(f);
            return 0;
        }

        count = list_add_after(count, value);

        if (start == NULL) start = count;
    }

    *list = start;
    fclose(f);

    if (errno) return 0;
    return 1;
}




