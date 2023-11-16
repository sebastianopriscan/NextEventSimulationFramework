#pragma once

#include "../events/event.h"

struct event_node {

    struct event *payload_event ;
    struct event_node *prev_node ;
    struct event_node *next_node ;
};

typedef struct event_queue {

    struct event_node *firstNode ;
    struct event_node *lastNode ;
} event_queue ;

void enqueue_event(struct event_queue *queue, struct event *event) ;

void append_event(struct event_queue *queue, struct event *event) ;

struct event *dequeue_event(struct event_queue *queue) ;

struct event_queue *create_queue() ;

void delete_queue(struct event_queue * queue) ;