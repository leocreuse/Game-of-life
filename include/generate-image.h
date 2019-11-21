/**
 * @file generate-image.h
 * 
 * @brief This file defines the functions used to generate the .ppm files to generate the gif.
 * 
 * @author Léo Creuse
 * 
 * There are two functions one can use: 
 *  -A function to generate a single frame from the state of the cells, 
 *  -A function generate the whole evolution, given a number of steps.
 */
#ifndef GENERATE_IMAGE_H
#define GENERATE_IMAGE_H

#include <stdio.h>
#include "cell.h"
#include "evolution.h"
#include <stdbool.h>
#include <string.h>


/**
 * @brief Creates a .ppm file representing the current population, including dying and newborn cells.
 * 
 * @param p_pop A pointer to the population to be rendered.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 * @param frame_number The output file will be named frame[image_number].ppm where [frame_number] is replace by the value of frame_number converted to text.
 */
void single_frame(population *p_pop, config *p_cfg, int frame_number);

/**
 * @brief Creates all the frames with the initial state p_pop and the settings given in p_cfg.
 * 
 * @param p_pop A pointer to the population 
 * 
 */

void all_frames(population *p_pop, config *p_cfg);

#endif
