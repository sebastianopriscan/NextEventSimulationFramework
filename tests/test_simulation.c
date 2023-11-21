#include <stdio.h>

#include "simulation/simulation.h"

void dummyStateModifier(struct simulation *sim, void *metadata) {
    char *state = (char *)sim->state;
    state[0] = 'H' ;
    state[1] = 'e' ;
    state[2] = 'l' ;
    state[3] = 'l' ;
    state[4] = 'o' ;
    state[5] = '\0' ;

    printf("Executed event at time %f\n\n", sim->clock) ;
}

void dummyStateEvolver(struct simulation *sim, void * metadata) {
    static int modulus = 0 ;
    static float time = 34.0f ;
    time = time +1 ;
    struct event *event1 = createEvent(time,dummyStateModifier, dummyStateEvolver, NULL) ;

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
    struct simulation *simulation1 = create_simulation(3,45.0f, state) ;

    struct event *event1 = createEvent(34.0f,dummyStateModifier, dummyStateEvolver, NULL) ;

    enqueue_event(simulation1->queues->queue, event1) ;

    run_simulation(simulation1) ;

    printf("%s\n", (char *)simulation1->state) ;

    return 0 ;
}