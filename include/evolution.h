/**
 * @file evolution.h
 * 
 * @brief Definition of the functions making possible the evolutionary steps of Conway's game of life.
 * 
 * @author Léo Creuse
 * 
 * This is the definitons of the functions enableling the evolutionary steps of the game.\n
 * The API consists of the following functions:\n
 *  -A function to transform all newborn cells in alive cells.\n
 *  -A function to kill (and delete) all dying cells from the population.\n
 *  -A function detemining which dead cells should be reborn due to their neighborhood,
 * 	and adding them to the population as newborns.\n
 *  -A function determining which cells should age and then die due to their neighborhood.\n\n
 * The order in which these functions should be used to complete one evolutionary step is:\n
 *  -all_alive\n
 * 	-kill_dying\n
 *  -age\n
 * 	-renew\n\n
 * All the functions have not been encapsulated into one in order to be able to see the dynamic of the game. 
 *  
 */
#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "cell.h"


/**
 * @brief Transforms all the newborn cells into alive cells.
 * 
 * @param  p_pop A pointer to the population to transform.
 */
void all_alive(population *p_pop);

/**
 * @brief Transforms all the dying cells in dead cells.
 * 
 * @param p_pop A pointer to the population to transform.
 */
void kill_dying(population *p_pop);

/**
 * @brief Creates new cells according to the evolution rules defined in the subject.
 * 
 * @param p_pop  A pointer to the population to transform.
 * @param original A pointer to the opulation to transform, it is only here to help with the recursion, it should be the same as p_pop in normal use.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 */
void renew(population *p_pop, config *p_cfg);

/**
 * @brief Transitions all the cells that should die a this step in the dying status.
 * 
 * @param p_pop  A pointer to the population to transfrom.
 */
void age(population *p_pop);

#endif
