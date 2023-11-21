#ifndef SIMULATION_H
#error You cannot include this header directly. Include "simulation/simulation.h" instead
#endif

#ifndef COMPILATION_H
#error "You're not compiling the library"
#endif

#ifndef EVENT_H
#define EVENT_H
#include "../simulation/simulation.h"

struct simulation ;
typedef void (*simulation_function)(struct simulation *sim, void *metadata) ;
 
struct event {

        double time ;
        simulation_function change_sim_state;
        simulation_function schedule_next_event;
        void *metadata ;
};

void consumeEvent(struct event *ev, struct simulation *sim) ;
#endif