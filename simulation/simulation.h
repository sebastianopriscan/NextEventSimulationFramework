#ifndef SIMULATION_H

#define SIMULATION_H

struct event ;

struct queue_list {
    struct event_queue *queue ;
    struct queue_list *next ;
};

struct simulation {

    double clock ;
    double simEnd ;
    int queue_number ;
    struct queue_list *queues ;
    char until_end; // 0: no (runs until simEnd); 1: at simEnd stops generating new events, processes the events already in queue

    void *state;
} ;

typedef void (*simulation_function)(struct simulation *sim, void *metadata) ;

struct simulation *create_simulation(int event_queues, double sim_end,  void *state) ;
struct simulation *create_simulation_until_end(int event_queues, double sim_end,  void *state) ;

int add_event_to_simulation(struct simulation *simulation, struct event *event, int queue_index) ;

void destroy_simulation(struct simulation *sim) ;

void run_simulation(struct simulation *sim) ;

struct event *createEvent(double time, simulation_function change_state_function,
        simulation_function schedule_func, void *metadata) ;

struct event *createUndiscardableEvent(double time, simulation_function change_state_function,
        simulation_function schedule_func, void *metadata) ;

// Deletes an event from the simulation (it frees the event). Metadata must be handled by the caller
void delete_event_from_simulation(struct simulation* sim, int queue_index, struct event *event);

#endif