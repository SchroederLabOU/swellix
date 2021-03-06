#ifndef __SWELLIX_SUBOPT_H
#define __SWELLIX_SUBOPT_H

#include "main.h"

typedef struct {
    int noLP;
    int noGU;
    int max_dist;
    int count;
    int constraints;
    int noML;
    int allpair;
    FILE * infile;
    FILE * outfile;
    int helix_badnesses;
    int helix_number;
    int helix_size;
    long statecount;
} options;

#define print(...) fprintf(OPTIONS.outfile, __VA_ARGS__)

#define MODIFIED_BASE -3
#define UNPAIRED_BASE -2

typedef enum {
  TIP, MULTI, LOOP,
} interval_flag;

typedef enum {
    IDLE, HALT, STATE
} mpi_flag;

typedef struct suboptinterval suboptinterval;
typedef int bool;

#define TRUE	  1
#define FALSE	  0
#define VERYBIG   1000000000

struct suboptinterval {
    int i;
    int j;
    interval_flag flag;
    suboptinterval *next;
};

typedef struct state_struct {
    suboptinterval *intervals;
    int *structure;
    int length; 
    char *sequence;
    int* constraints;
} state;

#define MIN_PAIR_DIST 3

int slide_those_windows(char* subSeq, char* subMod, int start, char* mods, int window, int tmms, int asymm, config* seq, LabeledStructures* labs, int* labsSize, int* labsMax);

void start(char *seq, int *constraints);
void start_with_constraints(state *s, int i);
void refine_state(state *s);
void refine_state_locally(state *s);

suboptinterval *make_interval(state *s, int ai, int aj, interval_flag aflag);
void unmake_interval(state *s);

void print_soln(state *s);
void print_state(state *s);

int allow_pair(state *s, int i, int j); 
int can_pair(char a, char b);
int constrained_to_not_pair(state *s, int i, int j);
int chemical_modification_ok(state *s, int i, int j);

int allow_state(state *s); 
int room_for_helices(state *s);
int helix_count(state *s);
int lonely_pair(state *s);

void set_args();
void subopt_print_usage();
int *interpreted_constraints(char *constraints);

void pstart(char *seq, int *constraints);
int * pack_state(state * S);
int *wait_for_state();
state *interpret_message(int *ints);

int label_struct(char* structure, int start);

#endif // __SWELLIX_SUBOPT_H
