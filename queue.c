// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

#include "queue.h"

void queue_add (Queue *q, void *item) {
  if (q->last) q->last = q->last->next = item;
  else q->first = q->last = item;
}

void _queue_insert (Queue *q, void *item, void *prev,
		    int (*compare) (void *a, void *b)) {
  q->first = _insert_sorted (q->first, item, prev, compare);
  if (q->last) {
    if (q->last->next) q->last = q->last->next;
  } else q->last = q->first;
}

void queue_insert (Queue *q, void *item,
		    int (*compare) (void *a, void *b)) {
  List *prev = NULL;
  _queue_insert (q, item, &prev, compare);
}

void *queue_remove (Queue *q) {
  void *item = q->first; 
  if (item) {
    if (q->first == q->last) queue_clear (q);
    else q->first = q->first->next;
  } return item;
}

void queue_free (Queue *q) {
  free_list (q->first); queue_clear (q);
}
