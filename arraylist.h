/*
 * A simple ArrayList to hold cells
 * Primarly intended for use in hashmap
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_
#define ARRAYLIST_INITIALSIZE 16

typedef int cell_t; //Temporary definition to work on arraylist without cell code

typedef struct{
	int numCells;
	int size;
	cell_t* array;
} arraylist_t;

/*
 * Initializes a new array list and returns a pointer to it
 */
arraylist_t* ArrayList_InitArrayList();
/*
 * Adds the cell to the arraylist at the given position
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Add(cell_t cell, int index, arraylist_t arraylist);
/*
 * Fills the cell pointer with the cell at the index in the arraylist
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Get(int index, arraylist_t arraylist, cell_t* cell);
/*
 * Removes the cell at the given position from the arraylist and puts it in the cell pointer
 * Returns 0 on success and -1 on invalid arguments
 * If a null pointer is passed in then simply removes the cell
 */
int arraylist_Remove(int index, arraylist_t arraylist, cell_t* cell);

#endif /* ARRAYLIST_H_ */
