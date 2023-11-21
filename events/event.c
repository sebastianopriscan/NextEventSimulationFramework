#include <stdlib.h>
#include <stdio.h>

#include "event.h"

struct event *createEvent(double time, void (*change_state_func)(struct simulation *sim, void *metadata),
                   void (*schedule_func)(struct simulation *sim, void *metadata), void *metadata) {

    struct event *retVal ;

    if((retVal = malloc(sizeof (struct event))) == NULL) {
        perror("Error in allocating memory for new event") ;
        return NULL ;
    }

    retVal->time = time ;
    retVal->change_sim_state = change_state_func ;
    retVal->schedule_next_event = schedule_func ;
    retVal->metadata = metadata ;

    return retVal ;
}

void consumeEvent(struct event *ev, struct simulation *sim) {

    if (ev->time <= sim->simEnd) {
        sim->clock = ev->time ;
        if(ev->change_sim_state != NULL)
            ev->change_sim_state(sim, ev->metadata) ;

        if(ev->schedule_next_event != NULL)
            ev->schedule_next_event(sim, ev->metadata) ;
    }

    free(ev) ;
}

