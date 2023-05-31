#include <stdio.h>

#include "simulation/simulation.h"

void dummyStateModifier(simulation *sim) {
    sim->state[0] = 'H' ;
    sim->state[1] = 'e' ;
    sim->state[2] = 'l' ;
    sim->state[3] = 'l' ;
    sim->state[4] = 'o' ;
    sim->state[5] = '\0' ;

    printf("Executed event at time %f\n\n", sim->clock) ;
}

void dummyStateEvolver(simulation *sim) {
    static int modulus = 0 ;
    static float time = 34.0f ;
    time = time +1 ;
    event *event1 = createEvent(time,dummyStateModifier, dummyStateEvolver) ;

    struct queue_list *queue = sim->queues ;

    for(int i = 0; i < modulus ; i++) {
        queue = queue->next ;
    }

    enqueue_event(queue->queue, event1) ;
    printf("Enqueued event at time %f in queue %d\n", time, modulus) ;

    modulus = (modulus+1)%3 ;
}

int main(void) {

    char state[45] ;
    simulation *simulation1 = create_simulation(3,3,45.0f, state) ;

    event *event1 = createEvent(34.0f,dummyStateModifier, dummyStateEvolver) ;

    enqueue_event(simulation1->queues->queue, event1) ;

    run_simulation(simulation1) ;

    printf("%s\n", simulation1->state) ;

    return 0 ;
}