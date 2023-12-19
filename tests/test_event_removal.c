#include <stdio.h>
#include <stdlib.h>
#include "simulation/simulation.h"

void increment_counter(struct simulation *simulation, void *metadata) {
  int *counter = (int *)simulation->state;
  *counter += 1;
}

void delete_event_test(struct simulation *simulation, void *metadata) {
  struct event* event = (struct event *)metadata;
  delete_event_from_simulation(simulation, 1, event);
}

int main(void) {
  int counter = 0 ;
  struct simulation* sim = create_simulation(2, 30, &counter);
  if (sim == NULL) {
    fprintf(stderr, "Error creating simulation\n");
    return 1;
  }

  struct event* event2 = createEvent(10, increment_counter, NULL, NULL) ;
  struct event* event = createEvent(5, increment_counter, delete_event_test, event2);
  add_event_to_simulation(sim, event, 0);
  add_event_to_simulation(sim, event2, 1);

  run_simulation(sim);

  if(counter != 1) return 1;

  destroy_simulation(sim);
  
  return 0;
}