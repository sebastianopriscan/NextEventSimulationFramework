#pragma once

struct event_node {

    event *payload_event ;
    struct event_node *next_node ;

};

typedef struct event_queue {

    struct event_node *firstNode ;
} event_queue ;

void *enqueue_event(struct event_queue *queue, event *event) ;

event *dequeue_event(struct event_queue *queue) ;

struct event_queue *create_queue() ;

void delete_queue(event_queue * queue) ;