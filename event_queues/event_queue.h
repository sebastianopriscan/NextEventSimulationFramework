#ifndef SIMULATION_H
#error You cannot include this header directly. Include "simulation/simulation.h" instead
#endif

#ifndef COMPILATION_H
#error "You're not compiling the library
#endif

#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#include "../events/event.h"

struct event;

struct event_node {

    struct event *payload_event ;
    struct event_node *prev_node ;
    struct event_node *next_node ;
};

struct event_queue {

    struct event_node *firstNode ;
    struct event_node *lastNode ;
} ;

void enqueue_event(struct event_queue *queue, struct event *event) ;

void append_event(struct event_queue *queue, struct event *event) ;

struct event *dequeue_event(struct event_queue *queue) ;

struct event_queue *create_queue() ;

void delete_queue(struct event_queue * queue) ;
#endif