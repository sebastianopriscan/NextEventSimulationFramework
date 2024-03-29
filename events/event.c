#include <stdlib.h>
#include <stdio.h>

#include "../simulation/simulation.h"
#include "event.h"

struct event *createUndiscardableEvent(double time, simulation_function change_state_function,
        simulation_function schedule_func, void *metadata) {
    
    struct event *retVal = createEvent(time, change_state_function, schedule_func, metadata) ;

    if(retVal != NULL) {
        retVal->discardable = 0 ;
    }

    return retVal ;
}


struct event *createEvent(double time, simulation_function change_state_function,
        simulation_function schedule_func, void *metadata) {

    struct event *retVal ;

    if((retVal = malloc(sizeof (struct event))) == NULL) {
        perror("Error in allocating memory for new event") ;
        return NULL ;
    }

    retVal->time = time ;
    retVal->change_sim_state = change_state_function ;
    retVal->schedule_next_event = schedule_func ;
    retVal->metadata = metadata ;
    retVal->discardable = 1;

    return retVal ;
}

void consumeEvent(struct event *ev, struct simulation *sim) {

    if (sim->until_end || ev->time <= sim->simEnd) {
        sim->clock = ev->time ;
        if(ev->change_sim_state != NULL)
            ev->change_sim_state(sim, ev->metadata) ;

        if(ev->schedule_next_event != NULL)
            ev->schedule_next_event(sim, ev->metadata) ;
    }

    free(ev) ;
}

