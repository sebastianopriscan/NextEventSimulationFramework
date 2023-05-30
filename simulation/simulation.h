#pragma once

#include "../event_queues/event_queue.h"

struct queue_list {
    struct event_queue *queue ;
    struct queue_list *next ;
};

typedef struct simulation {

    double clock ;
    double simEnd ;
    int queue_number ;
    struct queue_list *queues ;

    char state[] ;
} simulation ;

simulation *create_simulation(int state_size, int event_queues, double sim_end, const char *state) ;

void destroy_simulation(struct simulation *sim) ;

void run_simulation(struct simulation *sim) ;