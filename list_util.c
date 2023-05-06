// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

#include "list_util.h"
#include "util.h"
#include <stddef.h>
#include <stdlib.h>

List *list_dup (List *list) {
  List *l, *prev = NULL, *head = NULL;
  foreach (l, list) {
    List *n = type_alloc (List);
    n->data = l->data;
    if (prev) prev->next = n;
    else head = prev = n;
  } return head;
}

void *list_cat (void *la, void *lb) {
  if (la) { List *prev, *n;
    foreach (n, la) prev = n;
    prev->next = lb; return la;
  } return lb;
}

void *list_reverse (void *list) {
  List *l = list, *rev = NULL;
  while (l != NULL) {
    List *n = l->next;
    l->next = rev;
    rev = l; l = n;
  } return rev;
}

void *partition (void *lb, void *list, void *x,
		 int (*compare) (void *a, void *b)) {
  List *a = NULL, **b = lb, *y = list, *next;
  while (y) { next = y->next;
    if (compare (x, y) < 0) {
      y->next = *b; *b = y;
    } else {
      y->next = a; a = y;
    } y = next;
  } return a;
}

void *quick_sort (void *list, int (*compare) (void *a, void *b)) {
  List *x = list, *a = NULL, *b = NULL;
  if (list_length (list) <= 1) return list;
  a = partition (&b, x->next, x, compare);
  a = quick_sort (a, compare);
  b = quick_sort (b, compare);
  x->next = b; return list_cat (a, x);
}
