#ifndef LIST_H
#define LIST_H

typedef struct _List {
  struct _List *next;
  char *name;
  void *data;
} List;

void free_list (void *list);
List *list_insert (List *l, void *data);
int list_length (void *l);
void *_find_by_data (List **prev, List *l, void *data);
void *find_by_data (List *list, void *data);
List *insert_unique (List *l, void *data);
List *list_delete (List *l, void *data);
List *list_subtract (List *la, List *lb);
List *list_intersect (List *la, List *lb);
List *list_union (List *la, List *lb);
void *list_remove (void *list, void *link);
void *_insert_sorted (void *list, void *item, List **prev, int (*compare) (void *a, void *b)); 
void *insert_sorted (void *list, void *item, int (*compare) (void *a, void *b));

#endif // LIST_H