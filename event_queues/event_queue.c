#include <stdlib.h>
#include <stdio.h>

#include "event_queue.h"

struct event_node *create_node(struct event *event) {

    struct event_node * node ;

    if((node = malloc(sizeof(struct event_node))) == NULL) {
        perror("Error in allocating memory event: ") ;
        return node ;
    }

    node->next_node = NULL ;
    node->payload_event = event ;

    return node ;
}

void destroy_node(struct event_node *node) {
    free(node) ;
}

void enqueue_event(struct event_queue *queue, struct event *event) {

    struct event_node *node = queue->firstNode ;

    if(node == NULL) {
        queue->firstNode = create_node(event) ;
    } else {

        struct event_node *prev ;
        do {
            prev = node ;
            node = node->next_node ;
        } while (node != NULL) ;

        prev->next_node = create_node(event) ;
    }
}

event *dequeue_event(struct event_queue *queue) {

    struct event_node * first = queue->firstNode ;
    if (first == NULL) {
        return NULL ;
    } else {
        event *retVal = first->payload_event ;

        queue->firstNode = queue->firstNode->next_node ;

        destroy_node(first) ;

        return retVal ;
    }
}

struct event_queue *create_queue() {
    struct event_queue * queue ;

    if((queue = malloc(sizeof(struct event_queue))) == NULL) {
        perror("Error in allocating memory event: ") ;
        return queue ;
    }

    queue->firstNode = NULL ;

    return queue ;
}

void delete_queue(struct event_queue * queue) {

    while (dequeue_event(queue) != NULL) ;

    free(queue) ;
}