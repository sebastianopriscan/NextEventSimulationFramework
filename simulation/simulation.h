#pragma once

typedef struct simulation {

    double clock ;
    double simEnd ;
    int queue_number ;
    struct queue_list *queues ;

    char state[] ;
} simulation ;

simulation *create_simulation(int state_size, int event_queues, double sim_end, const char *state) ;

inline void destroy_simulation(struct simulation *sim) ;

void run_simulation(struct simulation *sim) ;