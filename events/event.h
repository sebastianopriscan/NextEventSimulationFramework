#pragma once

#include "../simulation/simulation.h"

typedef struct event {

        double time ;
        void (*change_sim_state)(simulation *sim) ;
        void (*schedule_next_event)(simulation *sim) ;
} event ;

event *createEvent(double time, void (*change_state_func)(simulation *sim), void (*schedule_func)(simulation *sim)) ;

void consumeEvent(struct event *ev, simulation *sim) ;