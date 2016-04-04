/*
 * A simple ArrayList to hold cells
 * Primarly intended for use in hashmap
 * TODO: Add more error checking to destroy method
 * TODO: Check to make sure arraylist has fields before using them
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
arraylist_t* arraylist_InitArraylist();

/*
 * Destroys the given arraylist, excluding the pointer to it
 * Returns 0 on success and -1 on invalid argument
 */
int arraylist_DestoryArraylist(arraylist_t* arraylist);

/*
 * Adds the cell to the arraylist at the given position
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Add(cell_t cell, int index, arraylist_t* arraylist);
/*
 * Fills the cell pointer with the cell at the index in the arraylist
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Get(int index, arraylist_t* arraylist, cell_t* cell);

/*
 * Checks if the arraylist contains the given cell
 * Returns 1 if it does, 0 if it doesn't, and -1 on
 * invalid arguments
 */
int arraylist_Contains(cell_t cell, arraylist_t* arraylist); //TODO: Change this after cell equality method is implemented.

/*
 * Removes the cell at the given position from the arraylist and puts it in the cell pointer
 * Returns 0 on success and -1 on invalid arguments
 * If a null pointer is passed in then simply removes the cell
 */
int arraylist_Remove(int index, arraylist_t* arraylist, cell_t* cell);

/*
 * Removes all copies of the given cell from the arraylist
 * If the cell is not in the arraylist, does nothing
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_RemoveCell(cell_t cell, arraylist_t* arraylist); //TODO: Change this after cell equality method is implemented

/*
 * Prints the arraylist to the console in a readable form
 * Returns 0 on success and -1 on invalid arguments
 */
int arraylist_Print(arraylist_t* arraylist);

#endif /* ARRAYLIST_H_ */
