#include <stdlib.h>
#include "meiro.h"
void shuffle_point_array(Point *array, int size){
    for(int i = 0; i < size; i++){
        int j = rand() % size;
        Point tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}
void shuffle_int_array(int *array, int size){
    for(int i = 0; i < size; i++){
        int j = rand() % size;
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}