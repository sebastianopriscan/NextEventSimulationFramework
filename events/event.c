#include <stdlib.h>
#include <stdio.h>

#include "event.h"

event *createEvent(double time, void (*change_state_func)(simulation *sim), void (*schedule_func)(simulation *sim)) {

    struct event *retVal ;

    if((retVal = malloc(sizeof (struct event))) == NULL) {
        perror("Error in allocating memory for new event") ;
        return NULL ;
    }

    retVal->time = time ;
    retVal->change_sim_state = change_state_func ;
    retVal->schedule_next_event = schedule_func ;


    return retVal ;
}

void consumeEvent(struct event *ev, struct simulation *sim) {

    if (ev->time <= sim->simEnd) {
        ev->change_sim_state(sim) ;
        ev->schedule_next_event(sim) ;
        sim->clock = ev->time ;
    }

    free(ev) ;
}

