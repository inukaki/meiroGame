#include "meiro_struct.h"

#define SMALL_X 21
#define SMALL_Y 11
#define MEDIUM_X 31
#define MEDIUM_Y 15
#define LARGE_X 41
#define LARGE_Y 21

void generate_mode(void);
void load_mode(void);
void play_mode(void);

void generate_meiro(char choice, Meiro *meiro);
void shuffle_point_array(Point *array, int size);
void shuffle_int_array(int *array, int size);
void play_meiro(Meiro *meiro);
void save_meiro(Meiro *meiro);
void load_meiro(Meiro *meiro);
void print_meiro(Meiro *meiro);
void print_answer(void);