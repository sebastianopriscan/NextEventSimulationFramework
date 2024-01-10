#include <stdio.h>
#include <stdlib.h>
#include "simulation/simulation.h"
#include "../event_queues/event_queue.h"

int values[4] = {5,7,10,12} ;

int main(void) {

  struct simulation* sim = create_simulation(2, 30, NULL);
  if (sim == NULL) {
    fprintf(stderr, "Error creating simulation\n");
    return 1;
  }

  struct event* event2 = createEvent(10, NULL, NULL, NULL) ;
  struct event* event = createEvent(5, NULL, NULL, NULL);
  struct event *event3 = createEvent(7, NULL, NULL, NULL) ;
  struct event *event4 = createEvent(12, NULL, NULL, NULL) ;
  
  
  add_event_to_simulation(sim, event2, 0);
  add_event_to_simulation(sim, event, 0);
  add_event_to_simulation(sim, event3, 0) ;
  add_event_to_simulation(sim, event4, 0) ;

  struct event_node *node = sim->queues->queue->firstNode ;
  struct event_node *prev ;
  int first = 1, index = 0 ;

  do {
    if (first) {
      if(node->prev_node != 0x0) return 1 ;

      if(node->payload_event->time != values[index]) return 1 ;

      prev = node ;
      node = node->next_node ;

      first = 0 ;
      index++ ;
      continue;
    }

    if(node->prev_node != prev) return 1 ;

    if(node->payload_event->time != values[index]) return 1 ;

    prev = node ;
    node = node->next_node ;

    index++ ;
  } while (node != NULL) ;

  destroy_simulation(sim);
  
  return 0;
}