#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simulation/simulation.h"

int result = 0 ;

void dummyStateEvolver(simulation *sim, void * metadata) ;

void checkStringsEqual(char *first, char *second) {
    if(strcmp(first,second)!= 0)
        result = 1 ;
}

void dummyStateModifier(simulation *sim, void *metadata) {
    sim->state[0] = 'H' ;
    sim->state[1] = 'e' ;
    sim->state[2] = 'l' ;
    sim->state[3] = 'l' ;
    sim->state[4] = 'o' ;
    sim->state[5] = '\0' ;

    checkStringsEqual((char *)(sim->state), "Hello") ;

    printf("Executed event at time %f\n\n", sim->clock) ;
}

void dummyModifierMetadata(simulation *sim, void *metadata) {
    sim->state[0] = ((char *)metadata)[0] ;
    sim->state[1] = ((char *)metadata)[1] ;
    sim->state[2] = ((char *)metadata)[2] ;
    sim->state[3] = ((char *)metadata)[3] ;
    sim->state[4] = ((char *)metadata)[4] ;
    sim->state[5] = '\0' ;

    checkStringsEqual((char *)(sim->state), "World") ;
}

void dummyEvolverMetadata(simulation *sim, void *metadata) {
    int queue = ((int *)metadata)[0] ;

    event *event1 = createEvent(40.0f, dummyModifierMetadata, dummyStateEvolver, (void *)((int *)(metadata) +1)) ;

    struct queue_list *list = sim->queues ;

    for (int i = 1 ; i <= queue; i++) {
        list = list->next ;
    }

    enqueue_event(list->queue,event1) ;
}

void dummyStateEvolver(simulation *sim, void * metadata) {
    event *event1 = createEvent(23.0f, NULL, NULL, NULL) ;

    enqueue_event(sim->queues->next->queue, event1) ;

}

int main(void) {

    char state[45] ;
    simulation *simulation1 = create_simulation(3,3,45.0f, state) ;

    void *metadata ;
    char *world = "World" ;

    if ((metadata = malloc(sizeof(int) + 6*sizeof(char))) == NULL) {
        perror("Error in allocating metadata") ;
        exit(1) ;
    }

    *((int *)metadata) = 2 ;

    memcpy((char *)((int *)(metadata)+1), world, 5) ;

    event *event1 = createEvent(10.0f, dummyStateModifier, dummyEvolverMetadata, metadata);

    enqueue_event(simulation1->queues->queue, event1) ;

    run_simulation(simulation1) ;

    printf("%s\n", simulation1->state) ;

    return result ;
}