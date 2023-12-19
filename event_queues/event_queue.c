#include <stdlib.h>
#include <stdio.h>

#include "../simulation/simulation.h"
#include "event_queue.h"

struct event_node *create_node(struct event *event) {

    struct event_node * node ;

    if((node = malloc(sizeof(struct event_node))) == NULL) {
        perror("Error in allocating memory event: ") ;
        return node ;
    }

    node->prev_node = NULL ;
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
        queue->lastNode = queue->firstNode ;
    } else {

        struct event_node *prev ;
        do {
            prev = node ;
            node = node->next_node ;
        } while (node != NULL || prev->payload_event->time <= event->time) ;

        prev->next_node = create_node(event) ;
    }
}

void append_event(struct event_queue *queue, struct event *event) {

    struct event_node *node = create_node(event) ;
    if (queue->lastNode == NULL) {
        queue->firstNode = node;
        queue->lastNode = queue->firstNode;
    } else {
        queue->lastNode->next_node = node ;
        node->prev_node = queue->lastNode ;
        queue->lastNode = node ;
    }
}

struct event *dequeue_event(struct event_queue *queue) {

    struct event_node * first = queue->firstNode ;
    if (first == NULL) {
        return NULL ;
    } else {
        struct event *retVal = first->payload_event ;

        queue->firstNode = queue->firstNode->next_node ;

        if(queue->firstNode != NULL)
            queue->firstNode->prev_node = NULL ;
        else
            queue->lastNode = NULL ;

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
    queue->lastNode = NULL ;

    return queue ;
}

void delete_queue(struct event_queue * queue) {

    while (dequeue_event(queue) != NULL) ;

    free(queue) ;
}

void delete_event(struct event_queue *queue, struct event *event)  {
    if (queue->firstNode == NULL) {
        return;
    }
    struct event_node *cursor = queue->firstNode;
    while(cursor != NULL && cursor->payload_event != event) {
        if(cursor == NULL) return ;
        cursor = cursor->next_node ;
    }
    if (cursor == NULL) return;

    if(cursor->prev_node != NULL) {
        cursor->prev_node->next_node = cursor->next_node;    
    } else {
        queue->firstNode = cursor->next_node;
    }
    
    if (cursor->next_node != NULL) {
        cursor->next_node->prev_node = cursor->prev_node;
    } else {
        queue->lastNode = cursor->prev_node;
    }
    destroy_node(cursor);
}
