/*
 * Represents a simple hashmap to hold cells
 * Note: This hashmap cannot hold dupicate cells
 * TODO: Add more error checking to destroy method
 * TODO: Fix the hash method when cells are implemented
 * TODO: Make numItems more secure in add/remove methods
 * TODO: Check to make sure hashmap has fields before using them
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_
#define HASHMAP_INITIALSIZE 16
#define HASHMAP_INITIALMAX 500

#include "arraylist.h"

typedef struct{
	arraylist_t** array; //Array of pointers
	int maxPercent;
	int size;
	int numCells;
} hashmap_t;

/*
 * Initializes a new (empty) hashmap and returns it
 */
hashmap_t* hashmap_InitHashmap();

/*
 * Destroys the given hashmap, except the pointer itself
 * Returns 0 on success and -1 on invalid arguments
 */
int hashmap_DestoryHashmap(hashmap_t* hashmap);

/*
 * Adds the given cell to the hashmap
 * If the cell is already in the map, does nothing
 * Returns 0 on success and -1 on invalid arguments
 */
int hashmap_Add(cell_t cell, hashmap_t* hashmap);

/*
 * Checks if the hashmap contains the given cell
 * Returns 1 if it does, 0 if it doesn't, and -1
 * on invalid argument
 */
int hashmap_Contains(cell_t cell, hashmap_t* hashmap);

/*
 * Removes the given cell from the hashmap
 * If the cell is not in the map, does nothing
 * Returns 0 on success and -1 on invalid argument
 */
int hashmap_Remove(cell_t cell, hashmap_t* hashmap);

/*
 * Prints the hashmap to the console in a readable manner
 * Returns 0 on success and -1 on invalid arguments
 */
int hashmap_Print(hashmap_t* hashmap);

#endif /* HASHMAP_H_ */
