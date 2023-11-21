#ifndef GENERIC_QUEUE_H
#define GENERIC_QUEUE_H

struct generic_queue_node {
  struct generic_queue_node *next;
  void *data;
};

struct generic_queue_list {
  struct generic_queue_node *head;
  struct generic_queue_node *tail;
};

struct generic_queue_list *create_queue_list() ;
void destroy_generic_queue_list(struct generic_queue_list *);

void *generic_dequeue_element(struct generic_queue_list *list) ;
int generic_enqueue_element(struct generic_queue_list *list, void *data) ;

#endif