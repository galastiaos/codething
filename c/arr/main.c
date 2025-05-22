#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    void *data;      // Pointer to hold data of any type
    size_t size;     // Number of elements in the array
    size_t capacity; // Capacity of the array
    size_t element_size; // Size of each element in the array
} DynamicArray;

// Initialize the dynamic array
void initArray(DynamicArray *arr, size_t initial_capacity, size_t element_size) {
    arr->data = malloc(initial_capacity * element_size);
    if (arr->data == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = initial_capacity;
    arr->element_size = element_size;
}

// Resize the array
void resizeArray(DynamicArray *arr, size_t new_capacity) {
    arr->data = realloc(arr->data, new_capacity * arr->element_size);
    if (arr->data == NULL) {
        printf("Memory reallocation failed.\n");
        exit(1);
    }
    arr->capacity = new_capacity;
}

// Add an element to the dynamic array
void add(DynamicArray *arr, void *value) {
    if (arr->size == arr->capacity) {
        resizeArray(arr, arr->capacity * 2);  // Double the size if full
    }
    // Copy the value to the array
    void *target = (char *)arr->data + arr->size * arr->element_size;
    memcpy(target, value, arr->element_size);
    arr->size++;
}

// Remove an element at the specified index
void remove_at(DynamicArray *arr, size_t index) {
    if (index >= arr->size) {
        printf("Index out of bounds.\n");
        return;
    }

    // Shift elements left to fill the gap
    for (size_t i = index; i < arr->size - 1; i++) {
        void *source = (char *)arr->data + (i + 1) * arr->element_size;
        void *destination = (char *)arr->data + i * arr->element_size;
        memcpy(destination, source, arr->element_size);
    }

    arr->size--;  // Reduce the size of the array
}

// Print the dynamic array (for int types, but can be modified for other types)
void printIntArray(const DynamicArray *arr) {
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d ", *(int *)((char *)arr->data + i * arr->element_size));
    }
    printf("\n");
}

// Free the dynamic array's memory
void freeArray(DynamicArray *arr) {
    free(arr->data);
}

int main() {
    DynamicArray arr;

    // Initialize the array to hold integers
    initArray(&arr, 2, sizeof(int)); //Initialize at the adress of arr, an initial capacity of 2, and each element being an integer(being the SIZE of an integer, could be any type)

    int x = 10, y = 20, z = 30; //initialize 3 integer
    add(&arr, &x);
    add(&arr, &y);
    add(&arr, &z);  // This will trigger a resize since the capacity is 2

    printf("Array after adding integer elements: ");
    printIntArray(&arr);

    remove_at(&arr, 1);  // Remove the element at index 1 (value 20)

    printf("Array after removing an element: ");
    printIntArray(&arr);

    // Now let's work with a dynamic array of floats
    DynamicArray floatArr;
    initArray(&floatArr, 2, sizeof(float));

    float a = 1.1, b = 2.2, c = 3.3;
    add(&floatArr, &a);
    add(&floatArr, &b);
    add(&floatArr, &c);  // This will trigger a resize since the capacity is 2

    printf("Array after adding float elements: ");
    printIntArray(&floatArr); // You'd need to create a print function for floats (not shown)

    freeArray(&arr);
    freeArray(&floatArr);

    return 0;
}

