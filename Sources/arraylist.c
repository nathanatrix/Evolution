/*
 * Implements the arraylist.h file
 */
#include "stdlib.h"
#include "arraylist.h"

//Hello Nathan!!

/*
 * Increases the size of the array
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_IncreaseSize(arraylist_t* arraylist);

/************************************************** PUBLIC METHODS ***********************************************/

/*
 * Initializes a new array list and returns a pointer to it
 */
arraylist_t* arraylist_InitArraylist() {
	arraylist_t* arraylist = (arraylist_t*)malloc(sizeof(arraylist_t));
	arraylist->size = ARRAYLIST_INITIALSIZE;
	arraylist->numCells = 0;
	arraylist->array = (cell_t*)malloc(sizeof(cell_t) * arraylist->size);
	return arraylist;
}

/*
 * Destroys the given arraylist, excluding the pointer to it
 * Returns 0 on success and -1 on invalid argument
 */
int arraylist_DestoryArraylist(arraylist_t* arraylist) {
	if(arraylist == 0) return -1;
	free(arraylist->array);
	return 0;
}

/*
 * Adds the cell to the arraylist at the given position
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Add(cell_t cell, int index, arraylist_t* arraylist) {
	if(arraylist == 0) return -1; //Check if null pointer
	if(index < 0 || index > arraylist->numCells) return -1;
	//Note: cell is local so it cannot be null
	if(arraylist->numCells == arraylist->size) arraylist_IncreaseSize(arraylist); //The array is full
	int i;
	for(i = arraylist->numCells; i >= index; i--) {
		arraylist->array[i+1] = arraylist->array[i];
	}
	arraylist->array[index] = cell;
	arraylist->numCells++;
	return 0;
}

/*
 * Fills the cell pointer with the cell at the index in the arraylist
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Get(int index, arraylist_t* arraylist, cell_t* cell) {
	if(arraylist == 0 || cell == 0) return -1; //Check if null pointers
	if(index < 0 || index >= arraylist->numCells) return -1;
	*cell = arraylist->array[index];
	return 0;
}

/*
 * Checks if the arraylist contains the given cell
 * Returns 1 if it does, 0 if it doesn't, and -1 on
 * invalid arguments
 */
int arraylist_Contains(cell_t cell, arraylist_t* arraylist) {
	if(arraylist == 0) return -1;
	int i;
	for(i = 0; i < arraylist->numCells; i++) {
		if(arraylist->array[i] == cell) return 1;
	}
	return 0;
}

/*
 * Removes the cell at the given position from the arraylist and puts it in the cell pointer
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Remove(int index, arraylist_t* arraylist, cell_t* cell) {
	if(arraylist == 0) return -1; //Check if null pointers
	if(index < 0 || index >= arraylist->numCells) return -1;
	if(cell != 0) *cell = arraylist->array[index]; //Copy the element to be deleted
	int i;
	for(i = index; i < arraylist->numCells - 1; i++) {
		arraylist->array[i] = arraylist->array[i+1];
	}
	arraylist->numCells--;
	return 0;
}

/*
 * Removes all copies of the given cell from the arraylist
 * If the cell is not in the arraylist, does nothing
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_RemoveCell(cell_t cell, arraylist_t* arraylist) {
	if(arraylist == 0) return -1;
	int i;
	for(i = 0; i < arraylist->numCells; i++) {
		if(arraylist->array[i] == cell) {
			arraylist_Remove(i--, arraylist, 0); //Remove the matching element and back up a step
		}
	}
	return 0;
}

/*
 * Prints the arraylist to the console in a readable form
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Print(arraylist_t* arraylist) {
	if(arraylist == 0) return -1;
	printf("[");
	int i;
	for(i = 0; i < arraylist->numCells; i++) {
		printf(i==0 ? "%d" : ",%d", arraylist->array[i]);
	}
	printf("]");
	return 0;
}

/*************************************** PRIVATE METHODS ***************************************************/

int arraylist_IncreaseSize(arraylist_t* arraylist) {
	if(arraylist == 0) return -1;
	cell_t* newArray = (cell_t*)malloc(arraylist->size * 2 * sizeof(cell_t));
	int i;
	for(i = 0; i < arraylist->numCells; i++) {
		newArray[i] = arraylist->array[i];
	}
	free(arraylist->array);
	arraylist->array = newArray;
	arraylist->size *= 2;
	return 0;
}
