/*
 * Implements the hashmap.h file
 */

#include "hashmap.h"
#include "arraylist.h"
#include "stdlib.h"
#include "stdio.h"

/*
 * The hash function for the hashmap
 */
int hashmap_Hash(cell_t cell, hashmap_t* hashmap);

/*
 * Expands the hashmap to twice its size
 * Returns 0 on success, -1 on invalid arguments,
 * and -2 on failure
 */
int hashmap_Expand(hashmap_t* hashmap);

/*************************************************** PUBLIC METHODS **************************************************/

/*
 * Initializes a new (empty) hashmap and returns it
 * Returns a null pointer on failure
 */
hashmap_t* hashmap_InitHashmap() {
	hashmap_t* hashmap = (hashmap_t*)malloc(sizeof(hashmap_t));
	if(hashmap == 0) return 0;
	hashmap->size = HASHMAP_INITIALSIZE;
	hashmap->maxPercent = HASHMAP_INITIALMAX;
	hashmap->numCells = 0;
	hashmap->array = (arraylist_t**)malloc(sizeof(arraylist_t*) * hashmap->size);
	int i;
	for(i = 0; i < hashmap->size; i++) {
		hashmap->array[i] = arraylist_InitArraylist(); //Initialize the arraylists
	}
	return hashmap;
}

/*
 * Destroys the given hashmap, except the pointer itself
 * Returns 0 on success and -1 on invalid arguments
 */
int hashmap_DestoryHashmap(hashmap_t* hashmap) {
	if(hashmap == 0) return -1;
	free(hashmap->array);
	return 0;
}

/*
 * Adds the given cell to the hashmap
 * If the cell is already in the map, does nothing
 * Returns 0 on success and -1 on invalid arguments
 */
int hashmap_Add(cell_t cell, hashmap_t* hashmap) {
	if(hashmap == 0) return -1;
	if(arraylist_Contains(cell, hashmap->array[hashmap_Hash(cell, hashmap)])) return 0; //Already in the hashmap
	if(hashmap->numCells * 100 > hashmap->size * hashmap->maxPercent) { //Exceeded the max percent
		if(hashmap_Expand(hashmap) < 0) { //Expand failed
			return -2;
		}
	}
	hashmap->numCells++;
	return arraylist_Add(cell, hashmap->array[hashmap_Hash(cell, hashmap)]->numCells, hashmap->array[hashmap_Hash(cell, hashmap)]);
}

/*
 * Checks if the hashmap contains the given cell
 * Returns 1 if it does, 0 if it doesn't, and -1
 * on invalid argument
 */
int hashmap_Contains(cell_t cell, hashmap_t* hashmap) {
	if(hashmap == 0) return -1;
	return arraylist_Contains(cell, hashmap->array[hashmap_Hash(cell, hashmap)]);
}

/*
 * Removes the given cell from the hashmap
 * If the cell is not in the map, does nothing
 * Returns 0 on success and -1 on invalid argument
 */
int hashmap_Remove(cell_t cell, hashmap_t* hashmap) {
	if(hashmap == 0) return -1;
	if(1 - arraylist_Contains(cell, hashmap->array[hashmap_Hash(cell, hashmap)])) return 0; //Does not contain cell
	int x = arraylist_RemoveCell(cell, hashmap->array[hashmap_Hash(cell, hashmap)]);
	if(x == 0) hashmap->numCells--; //The removal succeeded
	return x;
}

/*
 * Prints the hashmap to the console in a readable manner
 * Returns 0 on success and -1 on invalid arguments
 */
int hashmap_Print(hashmap_t* hashmap) {
	if(hashmap == 0) return -1;
	printf("{");
	int i;
	for(i = 0; i < hashmap->size; i++) {
		printf(" ");
		arraylist_Print(hashmap->array[i]);
	}
	printf(" }");
	return 0;
}

/******************************************** PRIVATE METHODS ***************************************************/

int hashmap_Hash(cell_t cell, hashmap_t* hashmap) {
	int r = cell % hashmap->size;
	while(r < 0) r+= hashmap->size; //Checking to make sure between 0 and hashmap->size
	while(r >= hashmap->size) r-=hashmap->size;
	return r;
}

int hashmap_Expand(hashmap_t* hashmap) {
	if(hashmap == 0) return -1;

	arraylist_t** newArray = (arraylist_t**)malloc(sizeof(arraylist_t*) * hashmap->size * 2);
	if(newArray == 0) return -2; //malloc failure
	arraylist_t** oldArray = hashmap->array; //Hold onto the old array

	hashmap->size *= 2; //Note: this is needed for the hash function to work
	int numCells = hashmap->numCells; //Hold onto in case of failure
	hashmap->numCells = 0; //Reset the number of cells because we will be changing it later

	int i, j;
	for(i = 0; i < hashmap->size; i++) {
		newArray[i] = arraylist_InitArraylist(); //Initialize the new arrays
		if(newArray[i] == 0) return -2; //InitArraylist failed
	}
	hashmap->array = newArray; //Set the new array into the hashmap, it's still empty
	for(i=0; i < hashmap->size / 2; i++) { //Iterate through arrays
		for(j=0; j < oldArray[i]->numCells; j++) { //Iterate through cells in array
			if(hashmap_Add(oldArray[i]->array[j], hashmap) < 0) { //Add the cells to the new array
				hashmap->size /= 2; //Reset the hashmap
				hashmap->array = oldArray;
				hashmap->numCells = numCells;
				return -2; //Add failed
			}
		}
	}
	for(i = 0; i < hashmap->size / 2; i++) {
		arraylist_DestoryArraylist(oldArray[i]); //Destroy the lists in the old array
	}
	free(oldArray); //Free the old array pointer
	return 0;
}
