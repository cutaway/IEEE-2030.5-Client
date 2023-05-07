#ifndef LIST_UTIL_H
#define LIST_UTIL_H

List *list_dup (List *list);
void *list_cat (void *la, void *lb);
void *list_reverse (void *list);
void *partition (void *lb, void *list, void *x, int (*compare) (void *a, void *b));
void *quick_sort (void *list, int (*compare) (void *a, void *b));

#endif // LIST_UTIL_H