#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
	void *data;
	size_t size;
	size_t capacity;
	size_t element_size;
} DynamicArray;

void initArray(DynamicArray *arr, size_t initial_capacity, size_t element_size);
void resizeArray(DynamicArray *arr,  size_t new_capacity);
void add(DynamicArray *arr, void *value);
void remove_at(DynamicArray *arr, size_t index);
void freeArray(DynamicArray *arr);
