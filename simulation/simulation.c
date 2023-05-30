#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "simulation.h"
#include "../events/event.h"
#include "../event_queues/event_queue.h"

struct queue_list {
    event_queue *queue ;
    struct queue_list *next ;
};

inline void destroy_simulation(struct simulation *sim) {

    struct queue_list *first = sim->queues ;

    if(first != NULL) {
        do {

            if(first->queue != NULL) {
                delete_queue(first->queue) ;
            }

            struct queue_list *next = first->next ;
            free(first) ;

            first = next ;

        } while (first != NULL) ;
    }

    free(sim) ;
}

event *getNextEvent(struct simulation *sim) {

    struct event *chosen = sim->queues->queue->firstNode->payload_event ;

    struct queue_list *currentQueue = sim->queues ;

    int remove_index = 0 ;

    for(int i = 1 ; i < sim->queue_number; i++) {

        currentQueue = currentQueue->next ;

        struct event *candidate = currentQueue->queue->firstNode->payload_event ;

        if (candidate->time <= chosen->time) {
            chosen = candidate ;
            remove_index = i ;
        }
    }

    currentQueue = sim->queues ;

    for (int i = 0 ; i < sim->queue_number ; i++) {
        if (remove_index == i)
            dequeue_event(currentQueue->queue) ;
        else
            currentQueue = currentQueue->next ;
    }

    return chosen ;
}

void run_simulation(struct simulation *sim) {

    event *nextEv = getNextEvent(sim) ;

    while (nextEv != NULL) {
        consumeEvent(nextEv, sim) ;
        nextEv = getNextEvent(sim) ;
    }
}

struct simulation *create_simulation(int state_size, int event_queues, double sim_end, const char *state) {
    struct simulation *sim ;

    if((sim = malloc(sizeof(struct simulation) + state_size)) == NULL) {
        perror("Error in allocating memory for simulation: ") ;
        return sim ;
    }

    memcpy(sim->state, state, state_size) ;

    sim->queue_number = event_queues ;
    sim->clock = 0.0 ;
    sim->simEnd = sim_end ;

    struct queue_list *list_head ;

    if((list_head = malloc(sizeof (struct queue_list))) == NULL) {
        perror("Error in allocating memory for simulation's queue lists: ") ;
        free(sim) ;

        return NULL ;
    }

    sim->queues = list_head ;

    struct queue_list *actual = list_head;

    for(int i = 0 ; i < state_size ; i++) {
        if((actual->queue = create_queue()) == NULL) {
            destroy_simulation(sim) ;

            return NULL ;
        }

        if (i == state_size-1) {
            actual->next = NULL ;
        } else {
            struct queue_list *newL ;

            if((newL = malloc(sizeof (struct queue_list))) == NULL) {
                perror("Error in allocating memory for simulation's queue lists: ") ;
                destroy_simulation(sim) ;
                return  NULL ;
            }

            actual = newL ;
        }
    }

    return sim ;
}