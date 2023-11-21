#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simulation/simulation.h"

int result = 0 ;

void dummyStateEvolver(struct simulation *sim, void * metadata) ;

void checkStringsEqual(char *first, char *second) {
    if(strcmp(first,second)!= 0)
        result = 1 ;
}

void dummyStateModifier(struct simulation *sim, void *metadata) {

    char *state = (char *) sim->state ;
    state[0] = 'H' ;
    state[1] = 'e' ;
    state[2] = 'l' ;
    state[3] = 'l' ;
    state[4] = 'o' ;
    state[5] = '\0' ;

    checkStringsEqual((char *)(sim->state), "Hello") ;

    printf("Executed event at time %f\n\n", sim->clock) ;
}

void dummyModifierMetadata(struct simulation *sim, void *metadata) {

    char *state = (char *) sim->state ;
    state[0] = ((char *)metadata)[0] ;
    state[1] = ((char *)metadata)[1] ;
    state[2] = ((char *)metadata)[2] ;
    state[3] = ((char *)metadata)[3] ;
    state[4] = ((char *)metadata)[4] ;
    state[5] = '\0' ;

    checkStringsEqual((char *)(sim->state), "World") ;
}

void dummyEvolverMetadata(struct simulation *sim, void *metadata) {
    int queue = ((int *)metadata)[0] ;

    struct event *event1 = createEvent(40.0f, dummyModifierMetadata, dummyStateEvolver, (void *)((int *)(metadata) +1)) ;
    add_event_to_simulation(sim, event1, queue);
}

void dummyStateEvolver(struct simulation *sim, void * metadata) {
    struct event *event1 = createEvent(23.0f, NULL, NULL, NULL) ;

    add_event_to_simulation(sim, event1, 1);

}

int main(void) {

    char state[45] ;
    struct simulation *simulation1 = create_simulation(3,45.0f, state) ;

    void *metadata ;
    char *world = "World" ;

    if ((metadata = malloc(sizeof(int) + 6*sizeof(char))) == NULL) {
        perror("Error in allocating metadata") ;
        exit(1) ;
    }

    *((int *)metadata) = 2 ;

    memcpy((char *)((int *)(metadata)+1), world, 5) ;

    struct event *event1 = createEvent(10.0f, dummyStateModifier, dummyEvolverMetadata, metadata);

    add_event_to_simulation(simulation1, event1, 0) ;

    run_simulation(simulation1) ;

    printf("%s\n", (char *) simulation1->state) ;

    return result ;
}