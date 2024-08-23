#include "fsm_header.h"
#include<stdio.h>

int main()
{
    struct state_t *state_q0, *state_q1;

    state_q0 = create_state("state_q0",fsm_true); // will instantiate state_q0
    state_q1 = create_state("state_q1",fsm_false); // will instantiate state_q1

    struct fsm *fsm;

    fsm = create_fsm("even_ones"); //will instantiate the finite state machine

    set_initial_state(fsm,state_q0); // will set the initial state

    //populating the transition table entries of state_q0
    create_tt_entry(&state_q0->state_trans_table,'1',state_q1);
    create_tt_entry(&state_q0->state_trans_table,'0',state_q0);
    //populating the transition table entries of state_q0
    create_tt_entry(&state_q1->state_trans_table,'1',state_q0);
    create_tt_entry(&state_q1->state_trans_table,'0',state_q1);

    int result;

    result = fsm_execute(fsm,"10101111",strlen("10101111"));

    (result)? printf("validated"):printf("rejeceted");

}
