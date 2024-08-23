//Various data structures required for the finite state machine
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TABLE_ENTRIES 256
#define MAX_STATE_NAME_SIZE 32
#define MAX_FSM_NAME_SIZE 128
enum Final_state{
  //bools for final state
    fsm_false,
    fsm_true
};
struct tt_entry{
  //transition table entry data structure
    char transition_key;
    struct state_t *next_state;
};
struct tt{
  //transition table
    struct tt_entry tt_e[MAX_TABLE_ENTRIES];
};
struct state_t{
    //name for state
    char name[MAX_STATE_NAME_SIZE];
    //transition table
    struct tt state_trans_table;
    //bool variable for checking whether a state is final or not
    enum Final_state is_final;
};
struct fsm{
  //name of the finite state machine
    char fsm_name[MAX_FSM_NAME_SIZE];
  //pointer to the initial state
    struct state_t *initial_state;
};


//Now the api's for the fsm

struct fsm *create_fsm(char name[])
{
    //this api will be used to instantiate a finite state machine
    struct fsm *new_fsm;
    new_fsm = calloc(1,sizeof(struct fsm));
    strncpy(new_fsm->fsm_name,name,strlen(name));
    return new_fsm;
};
struct state_t *create_state(char name[],enum Final_state state)
{
    //this api will be used to instantiate a generic state
    struct state_t *new_state;
    new_state = calloc(1,sizeof(struct state_t));
    strncpy(new_state->name,name,strlen(name));
    new_state->is_final = state;
    return new_state;
};
struct tt_entry *get_next(struct tt *table)
{
   /*for inserting an entry in the transition table we need to find the empty
   transition table entry this funtion will do the thing*/
    struct tt_entry *ptr;
    int i =0;
    while(1)
    {
        ptr = &table->tt_e[i];

        if(ptr->next_state==0)
            break;
        i++;
    }
    return ptr;
};

void create_tt_entry(struct tt *table,char transition_key,struct state_t *next_state)
{
  //api for populating transition table entry
    struct tt_entry *tt_ptr;
    tt_ptr = get_next(table);
    tt_ptr->next_state = next_state;
    tt_ptr->transition_key = transition_key;
}



void set_initial_state(struct fsm *fsm_,struct state_t *initial_state)
{
  //api for setting initial state
    fsm_->initial_state = initial_state;
}

struct state_t *match(struct state_t *current_state,char key)
{
  //this funtion will be used to match input charater with transition keys of the state
    struct tt *table;
    table = &current_state->state_trans_table;
    struct tt_entry *tt_e;
    struct state_t *next_state;
    int entry = 0;
    while(1)
    {
        tt_e = &table->tt_e[entry];
        if(tt_e->transition_key == key){
            next_state = tt_e->next_state;
            break;
        }
        entry++;
    }
    return next_state;
};

int fsm_execute(struct fsm *fsm_,char *input,int length)
{
    //this funtion will basically execute the algorithm of finite state machine
    printf("Input String: %s\n",input );
    struct state_t *current_state,*next_state;
    current_state = fsm_->initial_state;
    next_state = 0;
    int cursor = 0;
    while(cursor<length)
    {
        printf("%s -> ",current_state->name);
        next_state = match(current_state,input[cursor]);
        current_state = next_state;
        printf("%s  | on key: %c\n",current_state->name,input[cursor]);
        next_state = 0;
        cursor++;
    }
    return current_state->is_final;
}
