// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

#include "list.h"
#include <stdlib.h>
#include <string.h>

void free_list (void *list) { List *l = list, *t;
  while (l) t = l, l = l->next, free (t);
}

List *list_insert (List *l, void *data) {
  List *n = malloc (sizeof (List));
  n->next = l; n->data = data;
  return n;
}

int list_length (void *l) {
  List *list = l; int length = 0;
  while (list) length++, list = list->next;
  return length;
}

void *_find_by_data (List **prev, List *l, void *data) {
  for (*prev = NULL; l; *prev = l, l = l->next) 
    if (l->data == data) return l;
  return NULL;
}

void *find_by_data (List *list, void *data) { List *prev;
  return _find_by_data (&prev, list, data);
}

List *insert_unique (List *l, void *data) { List *prev;
  if (_find_by_data (&prev, l, data)) return l;
  return list_insert (l, data);
}

List *list_delete (List *l, void *data) { List *d, *prev;
  if (d = _find_by_data (&prev, l, data)) {
    if (prev) prev->next = d->next;
    else l = d->next; free (d);
  } return l;
}

List *list_subtract (List *la, List *lb) { List *b;
  foreach (b, lb) la = list_delete (la, b->data);
  return la;
}

List *list_intersect (List *la, List *lb) {
  List *a = la, *prev = (List *)&la, *next;
  while (a) { next = a->next;
    if (!find_by_data (lb, a->data)) {
      prev->next = next; free (a);
    } a = next;
  } return la;
}

List *list_union (List *la, List *lb) { List *b;
  foreach (b, lb)
    la = insert_unique (la, b->data);
  return la;
}

void *list_remove (void *list, void *link) { 
  List *l, *prev = (List *)&list;
  foreach (l, list) {
    if (l == link) {
      prev->next = l->next; break;
    } prev = l;
  } return list;
}

void *_insert_sorted (void *list, void *item, List **prev,
		      int (*compare) (void *a, void *b)) {
  List *l = list, *n = item;
  while (l && (compare (n, l) > 0))
    *prev = l, l = l->next;
  if (*prev) (*prev)->next = n; else list = n;
  n->next = l; return list;
}

void *insert_sorted (void *list, void *item,
		    int (*compare) (void *a, void *b)) {
  List *prev = NULL;
  return _insert_sorted (list, item, &prev, compare);
}
