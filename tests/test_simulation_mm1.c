#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "simulation/simulation.h"
#include "rngs.h"
#include "rvgs.h"

double arrivals[4096*1000] = {0.0};

struct simulation_state {
    double lmba ;
    double mu ;
    unsigned int n_Clients ;

    unsigned char status ;

    unsigned int total_clients_arrived;
    double last_arrival ;
    double total_arrival_times ;
    unsigned int total_clients;
    double total_service_time;
    double total_delay;
};

struct simulation_state *init_state(double lmba, double mu)
{
    struct simulation_state *val;
    if((val = malloc(sizeof(struct simulation_state))) == NULL)  {
        perror("Failed to allocate simulation state");
        exit(1);
    }

    val->lmba =lmba;
    val->mu = mu;
    val->n_Clients = 0;

    val->total_clients_arrived = 0;
    val->last_arrival = 0.0;
    val->total_clients = 0 ;
    val->total_service_time = 0.0;
    val->total_delay = 0.0;
    val->status = 0;
    
    return val;
}

void destroy_state(struct simulation_state *state)
{
    free(state) ;
}

void server_activate(struct simulation *sim, void *metadata)
{
  SelectStream(1) ;
  struct simulation_state *state = (struct simulation_state*) sim->state;

  double service_time = 0.0;
  
  if (state->n_Clients > 0) {
    service_time = Exponential(1.0 / state->mu) ;
    state->n_Clients -= 1;
    state->total_service_time += service_time ;
    state->total_clients += 1;
    state->total_delay += sim->clock;
    state->status = 1;

    double next = sim->clock + service_time;

    struct event* event = createEvent(next, server_activate, NULL, NULL);
    add_event_to_simulation(sim, event, 1);
  } else {
    state->status = 0;
  }
}

void arrivalPayload(struct simulation *sim, void *metadata) {

    struct simulation_state *state = (struct simulation_state *)(sim->state) ;

    state->n_Clients += 1 ;
    state->total_arrival_times += sim->clock;
    state->last_arrival = sim->clock;
    arrivals[state->total_clients_arrived] = sim->clock;
    state->total_clients_arrived += 1;

    if(state->status == 0)
    {
      struct event * event = createEvent(sim->clock, server_activate, NULL, NULL) ;
      add_event_to_simulation(sim, event, 1);
    }
}

void next_arrival(struct simulation *sim, void *metadata) {

    SelectStream(0) ;

    double inter = Exponential(1.0/((struct simulation_state *)(sim->state))->lmba) ;

    double time = sim->clock + inter;

    struct event *event1 = createEvent(time, arrivalPayload, next_arrival, NULL) ;

    add_event_to_simulation(sim, event1, 0);
}

struct simulation *run_single_simulation(double lambda, double mu) {
    struct simulation_state* state = init_state(lambda, mu);
    struct simulation *sim = create_simulation( 2, 100000, (char *) state);
    struct event *event = createEvent(0.0, arrivalPayload, next_arrival, NULL);
    enqueue_event(sim->queues->queue, event);
    run_simulation(sim);
    destroy_state(state);
    return sim ;
}

int main(void) {

    PlantSeeds(12345) ;
    
    struct simulation *sim = run_single_simulation(4.0, 5.0) ;

    struct simulation_state *state = (struct simulation_state *)(sim->state) ;

    if(1 / (state->last_arrival / state->total_clients) - 4.0 > 0.5) return 1 ;

    if(1 / (state->total_service_time / state->total_clients) - 5.0 > 0.5) return 1 ;

    double total_arrival = 0.0;
    for (int i = 0; i < state->total_clients; i++)
    {
      total_arrival += arrivals[i];
    }

    if((state->total_delay - total_arrival) / state->total_clients - 0.8 > 0.5) return 1 ;

    return 0;
}
