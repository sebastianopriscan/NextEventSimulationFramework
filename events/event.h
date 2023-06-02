#pragma once

#include "../simulation/simulation.h"

typedef struct event {

        double time ;
        void (*change_sim_state)(struct simulation *sim, void *metadata) ;
        void (*schedule_next_event)(struct simulation *sim, void *metadata) ;
        void *metadata ;
} event ;

event *createEvent(double time, void (*change_state_func)(struct simulation *sim, void *metadata),
        void (*schedule_func)(struct simulation *sim, void *metadata), void *metadata) ;

void consumeEvent(struct event *ev, struct simulation *sim) ;