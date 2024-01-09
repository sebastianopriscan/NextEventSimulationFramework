#include <stdio.h>
#include <stdlib.h>
#include "simulation/simulation.h"

int main(void) {

  struct simulation* sim = create_simulation(2, 30, NULL);
  if (sim == NULL) {
    fprintf(stderr, "Error creating simulation\n");
    return 1;
  }

  struct event* event2 = createEvent(10, NULL, NULL, NULL) ;
  struct event* event = createEvent(5, NULL, NULL, NULL);
  struct event *event3 = createEvent(7, NULL, NULL, NULL) ;
  
  add_event_to_simulation(sim, event2, 0);
  add_event_to_simulation(sim, event, 0);
  add_event_to_simulation(sim, event3, 0) ;

  destroy_simulation(sim);
  
  return 0;
}