#include <stdlib.h>
#include <stdio.h>

#include "generic_queue.h"

struct generic_queue_list *create_queue_list() {
  struct generic_queue_list *queue = malloc(sizeof(struct generic_queue_list));
  if (queue == NULL) {
    perror("Unable to allocate generic_queue_list");
    return NULL;
  }

  queue->head = queue->tail = NULL ;
  return queue;
}

void destroy_generic_queue_list(struct generic_queue_list * list){

    while(list->head != NULL)
        generic_dequeue_element(list) ;

    free(list) ;
}

void *generic_dequeue_element(struct generic_queue_list *list) {
  struct generic_queue_node* head = list->head;
  if (head == NULL)
    return NULL;
  
  void *data = head->data;
  list->head = list->head->next;  

  if (list->head == NULL)
    list->tail = NULL;

  free(head);
  return data;
}

int generic_enqueue_element(struct generic_queue_list *list, void *data) {
    
    struct generic_queue_node* node ;

    if((node = malloc(sizeof(struct generic_queue_node))) == NULL) {
        perror("Unable to allocate queue") ;
        return -1 ;
    }

    node->next = NULL;
    node->data = data ;

    struct generic_queue_node *tail = list->tail ;
    if (tail == NULL)
      list->head = node;
    else
      tail->next = node ;
    
    list->tail = node ;

    return 0;
}

void generic_remove_element(struct generic_queue_list *list, void *data) {
  if (list->head == NULL) return;

  struct generic_queue_node *prev_cursor = NULL;
  struct generic_queue_node *cursor = list->head;
  while(cursor != NULL && cursor->data != data) {
    prev_cursor = cursor;
    cursor = cursor->next;
  }
  if (cursor == NULL) return;

  if (prev_cursor != NULL) {
    prev_cursor->next = cursor->next;
  } else {
    queue->head = cursor->next;
  }

  if (cursor->next == NULL) {
    queue->tail = prev_cursor;
    prev_cursor->next = NULL;
  }
  free(cursor);
}
