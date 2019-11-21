/**
 * @file cell.h
 * 
 * @brief Definition of the cells constituting the alive population
 * 		  of the game of life.
 * 
 * @author Léo Creuse
 * 
 * This is the definition file for the cells constituting the alive 
 * population of the assignment's implementation of Conway's game of life.
 * Each cell contains various informations: it's status, it's position, a list 
 * of pointers to it's neighbors and a pointer to the next cell in the list storing
 * the entire alive population of the simulation.			
 * 
 *  the API is defined as follow:\n
 * 	-a function to initialize an empty population\n
 * 	-a function to create a newborn cell, given it's coordinates\n
 * 	-a function to know the size of the population\n
 * 	-a function to kill the first cell of the population\n
 *  -a function to deallocate the entire population\n
 * 	-a function to print in the console the list of the cells constituting the  
 * 	   population with their coordinates and their status.
 *  
 */
#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**
 * @brief An alias for the structure representing the cells.
 */
typedef struct cell cell;

/**
 * @brief An alias for the population: it's a pointer to the first cell.
 */
typedef cell* population; 

/**
 * @brief An enumaration to store the status of the cells.
 */
typedef enum {NEWBORN, ALIVE, DYING} status;

typedef struct config config;

/**
 * @brief The structure representing the cells.
 */
struct cell{
	status stat;/**< the status of the cell*///problems here when generating doc, the order is not preserved.
	int x;      /**< the first coordinate of the cell*/
	int y;      /**< the second coordinate of the cell*/
	cell *next; /**< a pointer to the next cell in the population*/
	cell *neigh[8];/**< a list of pointers to the neighbors of the cell*/
};

/**
 * @brief A structure containing parameters for the application. This makes it easier to add functionalities in the future.
 * 
 */
struct config{
	int x;       /**< the width of the simulation to be displayed*/
	int y;       /**< the height of the simulation */
	int pix;     /**< the width in pixels of a cell when using the GUI*/
	int it;      /**< the number of iteration to be rendered. When using the GUI, a negative value will render frames until the program is stopped.*/
	int trans;   /**< enables rendering transitions if is non zero.*/
	int pausable;/**< enables pausing the animation when using the GUI.*/
	int dy_r;    /**< The red component when rendering a dying cell.*/
	int dy_g;	 /**< The green component when rendering a dying cell.*/
	int dy_b;    /**< The blue component when rendering a dying cell.*/
	int al_r;    /**< The red component when rendering an alive cell.*/
	int al_g;    /**< The green component when rendering an alive cell.*/
	int al_b;    /**< The blue component when rendering an alive cell.*/
	int nb_g;    /**< The red component when rendering a newborn cell.*/
	int nb_r;    /**< The green component when rendering a newborn cell.*/
	int nb_b;    /**< The blue component when rendering a newborn cell.*/
	int delay;   /**< The delay in milliseconds between each frame.*/
};
/**
 * @brief Creates an empty population.
 * 
 * @param p_pop A pointer to the population.
 * 
 */
void nil(population *p_pop);

/**
 * @brief Adds a newborn cell to the population.
 * 
 * @param p_pop  A pointer to the population to which the cell should be added.
 * @param x   The first coordinate of the new cell.
 * @param y   The second coordiante to the new cell.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 */
void create_cell(population *p_pop, int x, int y, config * p_cfg);

/**
 * @brief Returns the number of cells constituting the population.
 * 
 * @param p_pop a pointer to the population which size is searched.
 * 
 * @return the number of cells in the population.
 */
int size(population *p_pop);

/**
 * @brief Removes (kills) the first cell of the population if there is one.
 * 
 * @param p_pop  A pointer to the population to which the cell should be killed.
 * 
 */
void kill_cell(population *p_pop);

/**
 * @brief Toggles a celle between the alive and dead state: If the cell in position (x,y) is dead , it will be replaced by an alive cell and vice-versa.
 * 
 * @param p_pop A pointer to the population on which to opperate.
 * @param x The first coordinate of the cell to toggle.
 * @param y The second coordinate of the cell to toggle.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 */

void toggle_cell(population *p_pop,int x, int y, config * p_cfg);

/**
 * @brief Deallocates an entire population.
 * 
 * @param p_pop the population to be deallocated.
 * 
 */
void deallocate_pop(population *p_pop);

/**
 * @brief Prints the list of cells in the console.
 * 
 * @param p_pop  The population to print.
 * 
 */
void print_pop(population *p_pop);
/**
 * @brief Prints a crude version of the map in the console.
 * 
 * @param p_pop the population representing the alive cells.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 */
void print_map(population *p_pop, config *p_cfg);

/**
 * @brief Prints the neighbors of the first cell of the population with this convention:\n
 *  -'_' for a dead cell\n
 *  -'/' for a newborn cell\n
 *  -'|' for an alive cell\n
 *  -'\' for a dying cell.
 * 
 * @param p_pop A pointer to the population which first cell's neighbors should be printed.
 */
void print_neighbors(population *p_pop);
#endif
