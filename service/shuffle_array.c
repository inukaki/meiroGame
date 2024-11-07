#include <time.h>
#include <stdlib.h>
#include "meiro.h"
void shuffle_array(Point *array, int size){
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        int j = rand() % size;
        Point tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}