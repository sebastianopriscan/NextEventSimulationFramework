#pragma once

#include "../event_queues/event_queue.h"

struct event ;

struct queue_list {
    struct event_queue *queue ;
    struct queue_list *next ;
};

struct simulation {

    double clock ;
    double simEnd ;
    int queue_number ;
    struct queue_list *queues ;

    void *state;
} ;

struct simulation *create_simulation(int event_queues, double sim_end,  void *state) ;

void add_event_to_simulation(struct simulation *simulation, struct event *event, int queue_index) ;

void destroy_simulation(struct simulation *sim) ;

void run_simulation(struct simulation *sim) ;