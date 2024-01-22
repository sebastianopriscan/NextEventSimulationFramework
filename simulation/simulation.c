#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "simulation.h"
#include "../event_queues/event_queue.h"
#include "../events/event.h"

void destroy_simulation(struct simulation *sim) {

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

struct event *getNextEvent(struct simulation *sim) {

    struct event *chosen = NULL;
    int remove_index = -1 ;

    if(sim->queues->queue->firstNode != NULL) {
        chosen = sim->queues->queue->firstNode->payload_event ;
        remove_index = 0 ;
    }

    struct queue_list *currentQueue = sim->queues ;

    for(int i = 1 ; i < sim->queue_number; i++) {

        currentQueue = currentQueue->next ;

        if(currentQueue->queue->firstNode == NULL) continue ;

        struct event *candidate = currentQueue->queue->firstNode->payload_event ;

        if (chosen == NULL || candidate->time <= chosen->time) {
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

    struct event *nextEv = getNextEvent(sim) ;

    while (nextEv != NULL) {
        consumeEvent(nextEv, sim) ;
        nextEv = getNextEvent(sim) ;
    }
}

struct simulation *create_simulation(int event_queues, double sim_end,  void *state) {
    struct simulation *sim ;

    if((sim = (struct simulation *) malloc(sizeof(struct simulation))) == NULL) {
        perror("Error in allocating memory for simulation: ") ;
        return sim ;
    }
    
    sim->queue_number = event_queues ;
    sim->clock = 0.0 ;
    sim->simEnd = sim_end ;
    sim->state = state;
    sim->until_end = 0;

    struct queue_list *list_head ;

    if((list_head = malloc(sizeof (struct queue_list))) == NULL) {
        perror("Error in allocating memory for simulation's queue lists: ") ;
        free(sim) ;

        return NULL ;
    }

    sim->queues = list_head ;

    struct queue_list *actual = list_head;

    for(int i = 0 ; i < event_queues ; i++) {
        if((actual->queue = create_queue()) == NULL) {
            destroy_simulation(sim) ;

            return NULL ;
        }

        if (i == event_queues-1) {
            actual->next = NULL ;
        } else {
            struct queue_list *newL ;

            if((newL = malloc(sizeof (struct queue_list))) == NULL) {
                perror("Error in allocating memory for simulation's queue lists: ") ;
                destroy_simulation(sim) ;
                return  NULL ;
            }

            actual->next = newL ;

            actual = newL ;
        }
    }

    return sim ;
}

struct simulation *create_simulation_until_end(int event_queues, double sim_end,  void *state) {
    struct simulation* sim = create_simulation(event_queues, sim_end, state);
    if (sim == NULL)
        return NULL;
    
    sim->until_end = 1;
    return sim;
}

int add_event_to_simulation(struct simulation *simulation, struct event *event, int queue_index)
{
    if (simulation->clock >= simulation->simEnd && simulation->until_end && event->discardable) return 1;
    if(queue_index >= simulation->queue_number) return 0;
    struct queue_list *queues = simulation->queues ;

    for (int i = 0; i < queue_index; i++)
    {
        queues = queues->next ;
    }

    enqueue_event(queues->queue, event) ;
    return 0;
}

void delete_event_from_simulation(struct simulation* sim, int queue_index, struct event *event) {
    struct queue_list *queues = sim->queues ;

    if(queue_index >= sim->queue_number) return ;
    for (int i = 0; i < queue_index; i++)
    {
        queues = queues->next ;
    }
    delete_event(queues->queue, event);
    free(event);
}